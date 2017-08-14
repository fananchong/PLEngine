import pl

def on_app_open():
    pl.set_log_level(pl.E_LOGGER_LEVEL.debug)
    pl.info("on_app_open")
    pl.warn("on_app_open")
    pl.error("on_app_open")
    
def on_app_close():
    pl.info("on_app_close")
