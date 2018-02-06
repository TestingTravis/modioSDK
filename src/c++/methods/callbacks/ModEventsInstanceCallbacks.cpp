#include "c++/ModIOInstance.h"

namespace modio
{
  std::map<u32, GetModEventsCall*> get_mod_events_calls;
  std::map<u32, GetAllModEventsCall*> get_all_mod_events_calls;
  SetModEventListenerCall* set_mod_event_listener_call;

  void onGetModEvents(void* object, ModioResponse modio_response, ModioModEvent* mod_events_array, u32 mod_events_array_size)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    std::vector<modio::ModEvent> mod_event_vector;
    mod_event_vector.resize(mod_events_array_size);
    for(u32 i=0; i < mod_events_array_size; i++)
    {
      mod_event_vector[i].initialize(mod_events_array[i]);
    }
    get_mod_events_calls[call_id]->callback((const Response&)response, mod_event_vector);

    delete get_mod_events_calls[call_id];
    delete (u32*)object;
    get_mod_events_calls.erase(call_id);
  }

  void onGetAllModEvents(void* object, ModioResponse modio_response, ModioModEvent* mod_events_array, u32 mod_events_array_size)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    std::vector<modio::ModEvent> mod_event_vector;
    mod_event_vector.resize(mod_events_array_size);
    for(u32 i=0; i < mod_events_array_size; i++)
    {
      mod_event_vector[i].initialize(mod_events_array[i]);
    }
    get_all_mod_events_calls[call_id]->callback((const Response&)response, mod_event_vector);

    delete get_all_mod_events_calls[call_id];
    delete (u32*)object;
    get_all_mod_events_calls.erase(call_id);
  }

  void onSetModEventListener(ModioResponse modio_response, ModioModEvent* mod_events_array, u32 mod_events_array_size)
  {
    modio::Response response;
    response.initialize(modio_response);

    std::vector<modio::ModEvent> mod_events_vector;
    mod_events_vector.resize(mod_events_array_size);
    for(u32 i=0; i < mod_events_array_size; i++)
    {
      mod_events_vector[i].initialize(mod_events_array[i]);
    }
    set_mod_event_listener_call->callback((const Response&)response, mod_events_vector);
  }
}
