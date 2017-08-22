import pl

def on_app_open():
    pl.trace("1.trace")
    pl.debug("2.debug")
    pl.info("3.info")
    pl.warn("4.warn")
    pl.error("5.error")
    pl.fatal("6.fatal")
    
    print("7.print")
    
    error_func()
    
def on_app_close():
    pl.info("on_app_close")
    
    
def error_func():
    import sssss
    pass
