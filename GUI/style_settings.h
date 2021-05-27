#ifndef MY_BASKET_STYLE_SETTINGS_H
#define MY_BASKET_STYLE_SETTINGS_H

#include <string>

namespace StyleSettings {

///поставить define на языки -- ифать внутри структур, чему присваивать строки
struct Titles {
    inline static const std::string windows_title = "My_Basket";
    inline static const std::string path_to_bg_image =
        "../data/image_basket2.jpg";

    // StartWindow
    inline static const std::string start_shopping_button_title =
        "start shopping!";
    inline static const std::string description_label_title =
        "your assistant in the selection of recipes";
    inline static const std::string choose_category_label_title =
        "Choose shops' category:";
    inline static const std::string economy_button_title = "economy";
    inline static const std::string base_button_title = "base";
    inline static const std::string premium_button_title = "premium";
    inline static const std::string go_to_searching_button = "go to searching!";

    // RecipeBook
    inline static const std::string product_name_label_title =
        "product or dish:";
    inline static const std::string recipe_label_product_title =
        "possible to take:";
    inline static const std::string recipe_label_recipe_title =
        "possible recipe:";
    inline static const std::string recipe_label_in_basket_title = "in basket:";
    inline static const std::string add_product_button_title = "add product";
    inline static const std::string add_recipe_button_title = "add recipe";
    inline static const std::string find_product_button_title = "find product";
    inline static const std::string put_in_basket_button_title =
        "put in basket";
    inline static const std::string find_recipe_button_title = "find recipe";
    inline static const std::string check_basket_button_title = "check basket";
    inline static const std::string choose_recipe_button_title =
        "choose recipe";
    inline static const std::string next_button_title = "next";
    inline static const std::string previous_button_title = "previous";

    //окна предупреждений
    inline static const std::string empty_input_window_title = "Empty input";
    inline static const std::string empty_input_window_text =
        "Please enter a product";
    inline static const std::string empty_basket_window_title = "Empty basket";
    inline static const std::string empty_basket_window_text =
        "Please add at least one product in the basket";

    // SummaryWindow
    inline static const std::string end_program_button_title = "end program";
    inline static const std::string best_total_cost_label_title =
        "best total cost:";
    inline static const std::string in_shop_label_title = "in shop:";
};

struct Colors {
    inline static const std::string pink_light_button = "";
    inline static const std::string pink_medium_button = "";
    inline static const std::string pink_hard_button = "";
    inline static const std::string green_label = "";
    inline static const std::string green_button = "";
    inline static const std::string blue_light_button = "";
    inline static const std::string blue_hard_button = "";
    inline static const std::string black = "black";
    inline static const std::string white = "white";
};

struct FontSizes {
    inline static const int my_basket_label_fz = 130;
    inline static const int description_label_fz = 27;
    inline static const int start_shopping_button_fz = 30;
    inline static const int category_window_buttons_fz = 20;
};

struct FontStyles {
    inline static const std::string bold = "bold";
};

struct WindowSizes {
    inline static const int min_width_window = 1000;
    inline static const int min_height_window = 600;
    inline static const int start_window_layout_spacing = 5;
    inline static const int my_basket_label_margin = 50;
};

struct Enable {
    bool enabled = true;
    bool unenabled = false;
};

struct ButtonSetting {};
struct ButtonsSettings {};
}  // namespace StyleSettings

#endif  // MY_BASKET_STYLE_SETTINGS_H
