#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

constexpr unsigned short HeightOfWidget = 32;
constexpr unsigned short WightOfWidget = 32 + 45;
constexpr unsigned short textSize = 9;

class IconTextWidget : public tgui::Panel
{

public:
    typedef std::shared_ptr<IconTextWidget> Ptr;
    typedef std::shared_ptr<const IconTextWidget> ConstPtr;

    // Add a constructor that sets the type name. This is the string that would be returned when calling getWidgetType().
    // We assume that we can keep the renderer of the base class in this code. See the "Changing renderer" section later
    // for an explanation on how to make changes to the renderer as well.
    IconTextWidget(const char* typeName = "MyCustomWidget", bool initRenderer = true) :
        tgui::Panel(typeName, initRenderer) /* base type depends on approach */
    {
    }

    // Copy constructors, assignment operators and destructor can be added if required for the members that
    // you add to the custom widget. These functions are not required by default.

    // Every widget needs a static create function which creates the widget and returns a smart pointer to it.
    // This function can have any parameters you want.
    static IconTextWidget::Ptr create()
    {
        return std::make_shared<IconTextWidget>();
    }

    // Every widget has a static method to copy it
    static IconTextWidget::Ptr copy(IconTextWidget::ConstPtr widget)
    {
        if (widget)
            return std::static_pointer_cast<IconTextWidget>(widget->clone());
        else
            return nullptr;
    }

protected:

    // Every widget needs a method to copy it
    Widget::Ptr clone() const override
    {
        return std::make_shared<IconTextWidget>(*this);
    }

	tgui::Picture::Ptr getPicture() { return mIcon; }
public:
	tgui::Picture::Ptr	mIcon;
	tgui::Label::Ptr	mText;
};
