#include "Server.h"

namespace server {

/**
 * @brief Listens to port 8080 and forwards the requests to the server. This
 * function never returns, and is meant to be called in its own thread.
 *
 */
void start_listener(std::shared_ptr<Server> server);

} // namespace server
