#include <work_with_string.h>
#include <QApplication>
#include <QtGui>
#include <iostream>
#include "algo.h"
#include "for_static.h"
#include "search_engine.h"
#include "additional_windows.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    std::string s = "Сода";
    std::vector<search::product> vec;
    API::ingredients_to_recipe::run_product_search(s, 5, vec);
    auto top_product = API::ingredients_to_recipe::show_res_of_request();
    for (const auto &t : top_product) {
        std::cout << t;
    }
    std::vector<search::Recipe> vec2;
    std::vector<search::product> ingr(1);
    ingr[0] = top_product[0];
    API::ingredients_to_recipe::run_recipes_search(ingr, 5, vec2);
    auto top_recipes = API::ingredients_to_recipe::show_recipes();
    for(auto& z: top_recipes){
        std::cout<<z.get_name()<<"\n";
    }
    auto q = API::ingredients_to_recipe::choose_recipe(0);
    auto t = API::ingredients_to_recipe::compare_prices_of_ingredients();
    std::cout << "\n----------------------------------------------------------";
    std::cout << "\n"
              << "The best shop: " << t.first.first << "\n";
    std::cout << "\n"
              << "Result sum: " << t.first.second << "\n";
    for (auto x : t.second) {
        std::cout << x.first << ": " << x.second << "\n";
    }

    // RecipeBook recipebook;
    // recipebook.show();

    Ui::StartWindow start_window;
    start_window.show();

    return app.exec();
}