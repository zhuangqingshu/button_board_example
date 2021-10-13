
set(COM_RQUIRES mcommon mwifi mlink mdebug light_driver light_handle mesh_utils button_driver buzzer_driver)


set(COM_SRCS "button.c")

idf_component_register(SRCS ${COM_SRCS}
                    INCLUDE_DIRS ""
                    REQUIRES ${COM_REQUIRES}
)
