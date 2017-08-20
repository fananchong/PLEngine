import pl

def on_app_open():
    pl.trace("on_app_open")
    pl.debug("on_app_open")
    pl.info("on_app_open")
    pl.warn("on_app_open")
    pl.error("on_app_open")
    pl.fatal("on_app_open")
    error_func()
    
def on_app_close():
    pl.info("on_app_close")
    
    
def error_func():
    import sssss
    pass
