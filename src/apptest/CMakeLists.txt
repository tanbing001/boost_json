set(BOOST_LIB ${Boost_LIBRARIES})

set(TARGETS
    value
	json_string
	json_array
	object
	number
	conversion
	custom_conversion
	initialize_list
)

foreach(name ${TARGETS})
	add_executable(${name} ${name}.cpp)
	target_link_libraries(${name} ${BOOST_LIB})
endforeach()
	