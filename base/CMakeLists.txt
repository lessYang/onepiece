aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/encoding S_ENCODING) 
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/crypto S_CRYPTO) 
set(O_BASE ${O_BASE} ${S_ENCODING} ${S_CRYPTO} PARENT_SCOPE)
