/**
 * @author ottojo
 * @date 1/25/21
 */

module;

#include <boost/json.hpp>

export module profiler.scope;

/**
 * Scope of an instant event
 */
export enum class Scope {
    Global, Process, Thread
};

export void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, Scope const &c) {
    switch (c) {
        case Scope::Global:
            jv = "g";
            break;
        case Scope::Process:
            jv = "p";
            break;
        case Scope::Thread:
            jv = "t";
            break;
    }
}
