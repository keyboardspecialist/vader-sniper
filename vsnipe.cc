#include <iostream>
#include <functional>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"


#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"  // for Ref

int main(int argc, const char* argv[]) {
  using namespace ftxui;

  std::string first_name;
  std::string last_name;
  std::string password;

  Component input_first_name = Input(&first_name, "first name");
  Component input_last_name = Input(&last_name, "last name");

  InputOption password_option;
  password_option.password = true;
  Component input_password = Input(&password, "password", password_option);

  auto component = Container::Vertical({
      input_first_name,
      input_last_name,
      input_password,
  });

  auto renderer = Renderer(component, [&] {
    return hbox ( {
                vbox({
                text("Hello " + first_name + " " + last_name),
                separator(),
                hbox(text(" First name : "), input_first_name->Render()),
                hbox(text(" Last name  : "), input_last_name->Render()),
                hbox(text(" Password   : "), input_password->Render()),
                }),
                hbox(text("Login Status : ")) 
            })
            | border;
  });

  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(renderer);
}
