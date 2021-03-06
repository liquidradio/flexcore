CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)

#ENABLE_TESTING()

# test_executable
ADD_EXECUTABLE( test_executable 
	examples.cpp
	core/test_connection.cpp
	core/test_connectables.cpp
	core/test_traits.cpp
	logging/test_logging.cpp
	nodes/test_buffer.cpp
	nodes/test_generic.cpp
	nodes/test_event_nodes.cpp
	nodes/test_state_nodes.cpp
	nodes/test_moving.cpp
	extended/graph/test_graph.cpp
	extended/nodes/test_base_node.cpp
	extended/nodes/test_infrastructure.cpp
	extended/nodes/test_region_worker_node.cpp
	extended/nodes/test_terminal_node.cpp
	extended/ports/test_event_buffer.cpp
	extended/ports/test_node_aware.cpp
	extended/ports/test_state_buffer.cpp
	pure/test_events.cpp
	pure/test_moving.cpp
	pure/test_mux_ports.cpp
	pure/test_state_sinks.cpp
	range/test_range.cpp
	runner.cpp 
	serialisation/test_deserializer.cpp
	settings/test_settings.cpp
	settings/test_setting_backend.cpp
	scheduler/TestClock.cpp
	scheduler/test_cyclecontrol.cpp
	scheduler/test_parallel_region.cpp
	scheduler/test_parallelscheduler.cpp
	scheduler/test_serialscheduler.cpp
	util/test_generic_container.cpp)

TARGET_INCLUDE_DIRECTORIES( test_executable 
	PRIVATE "." )

TARGET_LINK_LIBRARIES( test_executable
	PUBLIC flexcore )

# declares a test with our executable
#ADD_TEST( NAME test WORKING_DIRECTORY "." COMMAND test_executable )
