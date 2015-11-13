#ifndef SRC_PORTS_EVENT_SOURCES_EVENT_SOURCES_HPP_
#define SRC_PORTS_EVENT_SOURCES_EVENT_SOURCES_HPP_

#include <cassert>
#include <functional>
#include <memory>
#include <vector>

#include <core/traits.hpp>
#include <core/connection.hpp>

#include <ports/port_traits.hpp>
#include <core/detail/active_connection_proxy.hpp>

#include <iostream>

namespace fc
{

/**
 * \brief minimal output port for events.
 *
 * fulfills active_source
 * can be connected to multiples sinks and stores these in a shared std::vector.
 *
 * \tparam event_t type of event stored, needs to fulfill copy_constructable.
 * \invariant shared pointer event_handlers != 0.
 */
template<class event_t>
struct event_out_port
{
	typedef event_t result_t;
	typedef typename detail::handle_type<event_t>::type handler_t;

	event_out_port() = default;
	event_out_port(const event_out_port&) = default;

	template<class... T>
	void fire(T... event)
	{
		static_assert(sizeof...(T) == 0 || sizeof...(T) == 1,
				"we only allow single events, or void events atm");
		assert(event_handlers);
		for (auto& target : (*event_handlers))
		{
			assert(target);
			target(event...);
		}
	}

	size_t nr_connected_handlers() const
	{
		assert(event_handlers);
		return event_handlers->size();
	}

	/**
	 * \brief connects new connectable target to port.
	 * \param new_handler the new target to be connected.
	 * \pre new_handler is not empty function
	 * \post event_handlers.empty() == false
	 */
	auto connect(handler_t new_handler)
	{
		assert(event_handlers);
		assert(new_handler); //connecting empty functions is illegal
		event_handlers->push_back(new_handler);

		assert(!event_handlers->empty());
		return port_connection<decltype(*this), handler_t>();
	}

private:

	// stores event_handlers in shared vector, since the port is stored in a node
	// but will be copied, when it is connected. The node needs to send
	// to all connected event_handlers, when an event is fired.
	typedef std::vector<handler_t> handler_vector;
	std::shared_ptr<handler_vector> event_handlers = std::make_shared<handler_vector>(0);
};

// traits
// TODO prefer to test this algorithmically
template<class T> struct is_port<event_out_port<T>> : public std::true_type {};

} // namespace fc

#endif /* SRC_PORTS_EVENT_SOURCES_EVENT_SOURCES_HPP_ */