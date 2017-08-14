
#ifdef ENABLE_PLENGINE_PYTHON

// https://github.com/jparise/python-reloader.git

#include <string>

static std::string Usage = R"(

Usage

The reloader works by tracking dependencies between imported modules. It must first be enabled in order to track those dependencies. The reloader has no dependency information for modules that were imported before it was enabled or after it is disabled, so you'll probably want to enable the reloader early in your application's startup process.

import reloader
reloader.enable()

# Import additional modules
import module1
import module2
To manually reload an imported module, pass it to the reloader's reload() method:

import example
reloader.reload(example)
Note that you must pass the module object itself and not a string containing the module's name. If you only have the module's name, you can fetch the module object from the global sys.modules dictionary:

reloader.reload(sys.modules['example'])
You can also query a module's dependencies for informational or debugging purposes:

reloader.get_dependencies(example)
You can disable the reloader's dependency tracking at any time:

reloader.disable()
Blacklisting Modules

There may be times when you don't want a module and its dependency hierarchy to be reloaded. The module might rarely change and be expensive to import. To support these cases, you can explicitly "blacklist" modules from the reloading process using the blacklist argument to enable().

reloader.enable(blacklist=['os', 'ConfigParser'])
The blacklist can be any iterable listing the fully-qualified names of modules that should be ignored. Note that blacklisted modules will still appear in the dependency graph for completeness; they will just not be reloaded.

An Interactive Example

This example demonstrates how easily the reloader can be used from the interactive Python interpretter. Imagine you have the module example.py open in a text editor, and it contains the following:

print "I am example.py"
Our interactive session starts like this:

>>> import reloader
>>> reloader.enable()
>>> import example
I am example.py
Now modify example.py in your text editor. You can then reload the example in your interactive session:

>>> reloader.reload(example)
I am the modified example.py
This is a simplistic example that doesn't fully demonstrate the power of the reloader's dependency-based module tracking, but it hopefully illustrates the basic usage and utility of the system.

The __reload__() Callback

If a module has a __reload__() function, it will be called with a copy of the original module's dictionary after it has been reloaded. This provides a convenient mechanism for preserving state between reloads.

Consider a module named counts that contains the following code:

COUNTER = 0
The module's COUNTER variable will be reset to 0 when the module is reloaded:

>>> import counts
>>> counts.COUNTER += 1
>>> counts.COUNTER
1
>>> reloader.reload(counts)
>>> counts.COUNTER += 1
1
We can preserve the value of COUNTER across reloads by adding a __reload__() function to the counts module:

def __reload__(state):
    global COUNTER
    COUNTER = state['COUNTER']
Now when we reload counts:

>>> import counts
>>> counts.COUNTER += 1
>>> counts.COUNTER
1
>>> reloader.reload(counts)
>>> counts.COUNTER += 1
>>> counts.COUNTER
2

)"
;

std::string python_reloader_string =
R"(

# Python Module Reloader
#
# Copyright (c) 2009-2015 Jon Parise <jon@indelible.org>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

"""Python Module Reloader"""

try:
    import builtins
except ImportError:
    import __builtin__ as builtins

import imp
import sys
import types

__author__ = 'Jon Parise <jon@indelible.org>'
__version__ = '0.6'

__all__ = ('enable', 'disable', 'get_dependencies', 'reload')

_baseimport = builtins.__import__
_blacklist = []
_dependencies = dict()
_parent = None

# Jython doesn't have imp.reload().
if not hasattr(imp, 'reload'):
    imp.reload = reload

# PEP 328 changed the default level to 0 in Python 3.3.
_default_level = -1 if sys.version_info < (3, 3) else 0

def enable(blacklist=None):
    """Enable global module dependency tracking.

    A blacklist can be specified to exclude specific modules (and their import
    hierachies) from the reloading process.  The blacklist can be any iterable
    listing the fully-qualified names of modules that should be ignored.  Note
    that blacklisted modules will still appear in the dependency graph; they
    will just not be reloaded.
    """
    global _blacklist
    builtins.__import__ = _import
    if blacklist is not None:
        _blacklist = frozenset(blacklist)

def disable():
    """Disable global module dependency tracking."""
    global _blacklist, _parent
    builtins.__import__ = _baseimport
    _blacklist = None
    _dependencies.clear()
    _parent = None

def get_dependencies(m):
    """Get the dependency list for the given imported module."""
    name = m.__name__ if isinstance(m, types.ModuleType) else m
    return _dependencies.get(name, None)

def _deepcopy_module_dict(m):
    """Make a deep copy of a module's dictionary."""
    import copy
    import types

    # We can't deepcopy() everything in the module's dictionary because some
    # items, such as '__builtins__', aren't deepcopy()-able.  To work around
    # that, we start by making a shallow copy of the dictionary, giving us a
    # way to remove keys before performing the deep copy.
    d = vars(m).copy()
    del d['__builtins__']
    tmp = []
    cobjs = {}
    for k, v in d.items():
        if type(v) == types.ModuleType:
            tmp.append(k)
    for t in tmp:
        del d[t]
    return d

def _reload(m, visited, t):
    """Internal module reloading routine."""
    name = m.__name__

    # If this module's name appears in our blacklist, skip its entire
    # dependency hierarchy.
    if _blacklist and name in _blacklist:
        return

    # Start by adding this module to our set of visited modules.  We use this
    # set to avoid running into infinite recursion while walking the module
    # dependency graph.
    visited.add(m)

    # Start by reloading all of our dependencies in reverse order.  Note that
    # we recursively call ourself to perform the nested reloads.
    deps = _dependencies.get(name, None)
    if deps is not None:
        for dep in reversed(deps):
            if dep not in visited:
                _reload(dep, visited, t)

    # Clear this module's list of dependencies.  Some import statements may
    # have been removed.  We'll rebuild the dependency list as part of the
    # reload operation below.
    try:
        del _dependencies[name]
    except KeyError:
        pass

    # Because we're triggering a reload and not an import, the module itself
    # won't run through our _import hook below.  In order for this module's
    # dependencies (which will pass through the _import hook) to be associated
    # with this module, we need to set our parent pointer beforehand.
    global _parent
    _parent = name

    # If the module has a __reload__(d) function, we'll call it with a copy of
    # the original module's dictionary after it's been reloaded.
    callback = getattr(m, '__reload__', None)
    if callback is not None:
        if t == 1:
            d = _deepcopy_module_dict(m)
            imp.reload(m)
            callback(d)
    else:
        if t == 0:
            imp.reload(m)

    # Reset our parent pointer now that the reloading operation is complete.
    _parent = None

def myreload(m, t):
    """Reload an existing module.

    Any known dependencies of the module will also be reloaded.

    If a module has a __reload__(d) function, it will be called with a copy of
    the original module's dictionary after the module is reloaded."""
    _reload(m, set(), t)

def _import(name, globals=None, locals=None, fromlist=None, level=_default_level):
    """__import__() replacement function that tracks module dependencies."""
    # Track our current parent module.  This is used to find our current place
    # in the dependency graph.
    global _parent
    parent = _parent
    _parent = name

    # Perform the actual import work using the base import function.
    base = _baseimport(name, globals, locals, fromlist, level)

    if base is not None and parent is not None:
        m = base

        # We manually walk through the imported hierarchy because the import
        # function only returns the top-level package reference for a nested
        # import statement (e.g. 'package' for `import package.module`) when
        # no fromlist has been specified.  It's possible that the package
        # might not have all of its descendents as attributes, in which case
        # we fall back to using the immediate ancestor of the module instead.
        if fromlist is None:
            for component in name.split('.')[1:]:
                try:
                    m = getattr(m, component)
                except AttributeError:
                    m = sys.modules[m.__name__ + '.' + component]

        # If this is a nested import for a reloadable (source-based) module,
        # we append ourself to our parent's dependency list.
        if hasattr(m, '__file__'):
            l = _dependencies.setdefault(parent, [])
            l.append(m)

    # Lastly, we always restore our global _parent pointer.
    _parent = parent

    return base

)";


#endif
