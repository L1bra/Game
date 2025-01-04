#include "menu_state.h"

MenuState::MenuState(StateStack& stack, Context context)
	:
	State(stack, context),
	m_gui_container()
{
	const sf::Vector2f view_size = context.m_window->get_view().getSize();
	const sf::VideoMode vm = context.m_window->get_gfx().resolution;

	m_background_shape.setSize({ static_cast<float>(vm.size.x), static_cast<float>(vm.size.y) });
	m_background_shape.setFillColor(sf::Color::Black);

	auto play_button = std::make_shared<GUI::Button>(*context.m_fonts, *context.m_textures);
	play_button->setPosition({ gui::p2px(80.f, vm), gui::p2py(40.f, vm) });
	play_button->set_characted_size(gui::calc_char_size(vm));
	play_button->set_text("Play");
	play_button->set_callback([this]()
		{
			request_stack_pop();
			request_stack_push(States::World);
		});

	auto settings_button = std::make_shared<GUI::Button>(*context.m_fonts, *context.m_textures);
	settings_button->setPosition({ gui::p2px(80.f, vm), gui::p2py(50.f, vm) });
	settings_button->set_characted_size(gui::calc_char_size(vm));
	settings_button->set_text("Settings");
	settings_button->set_callback([this]()
		{
			request_stack_push(States::Settings);
		});

	auto exit_button = std::make_shared<GUI::Button>(*context.m_fonts, *context.m_textures);
	exit_button->setPosition({ gui::p2px(80.f, vm), gui::p2py(60.f, vm) });
	exit_button->set_characted_size(gui::calc_char_size(vm));
	exit_button->set_text("Exit");
	exit_button->set_callback([this]()
		{
			request_stack_pop();
		});

	m_gui_container.pack(play_button);
	m_gui_container.pack(settings_button);
	m_gui_container.pack(exit_button);
}

void MenuState::draw()
{
	Window& window = *get_context().m_window;

	window.set_view(window.get_default_view());

	window.draw(m_background_shape);
	window.draw(m_gui_container);
}

bool MenuState::update(sf::Time dt)
{
	return true;
}

bool MenuState::handle_event(const std::optional<sf::Event> event)
{
	m_gui_container.handle_event(event);
	return false;
}