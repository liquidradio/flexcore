// std
#include <functional>

// boost
#include <boost/test/unit_test.hpp>

#include <core/connection.hpp>
#include <ports/state_ports.hpp>

using namespace fc;

namespace // unnamed
{
template<class data_t>
struct node_class
{
	node_class(data_t v = data_t())
		: port(std::bind( &node_class<data_t>::get_value, this ))
		, value(v)
	{}

	data_t get_value() { return value; }

	typedef state_source_call_function<data_t> port_t;
	port_t port;

	data_t value;
};
} // unnamed namespace

BOOST_AUTO_TEST_CASE( stream_query_node_simple_case )
{
	node_class<int> node;
	state_sink<int> sink;

	node.port >> sink;

	BOOST_CHECK(sink.get() == 0);
	node.value = 5;
	BOOST_CHECK(sink.get() == 5);
	BOOST_CHECK(sink.get() == 5);
}

BOOST_AUTO_TEST_CASE( stream_query_multiple_sinks )
{
	node_class<int> node;
	auto increment = [](int i) -> int { return i+1; };
	state_sink<int> sink1;
	state_sink<int> sink2;

	node.port >> increment >> sink1;
	node.port >> increment >> sink2;

	BOOST_CHECK(sink1.get() == 1);
	BOOST_CHECK(sink2.get() == 1);
	node.value = 5;
	BOOST_CHECK(sink1.get() == 6);
	BOOST_CHECK(sink2.get() == 6);
}