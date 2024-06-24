/**
 * @author ottojo
 * @date 1/25/21
 */

module;
#include <simdjson.h>


export module profiler.scope;

/**
 * Scope of an instant event
 */
export enum class Scope { Global, Process, Thread };

