#ifndef SRC_PORTS_STREAM_SOURCES_STREAM_QUERY_FUNCTION_HPP_
#define SRC_PORTS_STREAM_SOURCES_STREAM_QUERY_FUNCTION_HPP_

// std
#include <functional>
#include <memory>

// fc

namespace fc
{

/**
 * State source port that queries a node for the value
 * See test_stream_query_node.cpp for sample use inside a node
 *
 * Caller is responsible that the node passed to the constructor is not destroyed before the port
 */
template<class data_t>
class state_source_call_function
{
public:
	/**
	 * \brief constructs state_source_function with function to call.
	 *
	 * \param f function which is called, when data is pulled from this source
	 * \pre f needs to be non empty function.
	 */
	explicit state_source_call_function(std::function<data_t()> f) : call(f)
	{
		assert(call);
	}

	data_t operator()()
	{
		return call();
	}

private:
	std::function<data_t()> call;
};

} // namespace fc

#endif /* SRC_PORTS_STREAM_SOURCES_STREAM_QUERY_FUNCTION_HPP_ */