#include "modio.h"

int main(void)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto wait = [&]() {
    while (!finished)
    {
      modio_instance.sleep(10);
      modio_instance.process();
    }
  };

  auto finish = [&]() {
    finished = true;
  };

  std::cout << "Listening to mod events..." << std::endl;

  // You can register a function as callback for mod events
  modio_instance.setEventListener([&](const modio::Response &response, const std::vector<modio::Event> &events) {
    // The mod event callback is triggered in a constant interval of time, 15 seconds by default
    std::cout << "On mod get response: " << response.code << std::endl;
    if (response.code == 200)
    {
      // it returns a vector of events so you can notify the user about it or do the correspoding changes
      for (auto &event : events)
      {
        std::cout << "Event found!" << std::endl;
        std::cout << "Id: " << event.id << std::endl;
        std::cout << "Mod id: " << event.mod_id << std::endl;
        std::cout << "User id: " << event.user_id << std::endl;
        std::cout << "Date added: " << ctime(&(time_t)event.date_added);
        std::cout << "Event Type: ";
        switch (event.event_type)
        {
        case MODIO_EVENT_UNDEFINED:
          std::cout << "Undefined" << std::endl;
          break;
        case MODIO_EVENT_MODFILE_CHANGED:
          std::cout << "Modfile changed" << std::endl;
          break;
        case MODIO_EVENT_MOD_AVAILABLE:
          std::cout << "Mod available" << std::endl;
          break;
        case MODIO_EVENT_MOD_UNAVAILABLE:
          std::cout << "Mod unavailable" << std::endl;
          break;
        case MODIO_EVENT_MOD_EDITED:
          std::cout << "Mod edited" << std::endl;
          break;
        }
        std::cout << std::endl;
      }
    }
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
