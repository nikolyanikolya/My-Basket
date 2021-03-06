// You may need to build the project (run Qt uic code generator) to get
#include "recipe_book.h"
#include <QBrush>
#include <QGridLayout>
#include <QMessageBox>
#include <QPalette>
#include <QSizePolicy>
#include <sstream>
#include "additional_windows.h"
#include "API.h"
#include "style_settings.h"

namespace Ui {

static void print_product_by_name(QTextEdit *text_field,
                                  search::product const &product) {
    std::string s = product.get_name() + '\n';
    text_field->insertPlainText(QString::fromUtf8(s.c_str()));
}

static void print_product_by_name_price(QTextEdit *text_field,
                                        search::product const &product) {
    print_product_by_name(text_field, product);
    std::string s =
        "----price:----\n" + std::to_string(product.get_price()) + "₽" + '\n';
    text_field->insertPlainText(QString::fromUtf8(s.c_str()));
}

static void print_recipe(QTextEdit *text_field, search::Recipe const &recipe) {
    std::string s = recipe.get_name() + '\n' + '\n' + "----ingredients:----\n";
    for (auto const &prod : recipe.get_ingredients()) {
        s += prod.get_name() + '\n';
    }
    text_field->insertPlainText(QString::fromUtf8(s.c_str()));
}

static void print_products_vector(
    QTextEdit *text_field,
    std::vector<search::product> const &products_vec) {
    int vec_sz = products_vec.size();
    for (int i = 0; i < vec_sz; i++) {
        std::string s = std::to_string(i + 1) + ") ";
        text_field->insertPlainText(s.c_str());
        print_product_by_name(text_field, products_vec[i]);
        text_field->insertPlainText("\n");
    }
}

void RecipeBook::button_enabled(QPushButton *button, bool is_enabled) {
    if (is_enabled) {
        set_font_color_button(
            button, StyleSettings::Colors::blue_light_button,
            StyleSettings::FontSizes::standard_medium_button_sz, true);
    } else {
        set_font_color_button(
            button, StyleSettings::Colors::blue_hard_button,
            StyleSettings::FontSizes::standard_medium_button_sz, false);
    }
}

void RecipeBook::update_buttons_enabled(bool add_product_button_enabled,
                                        bool add_recipe_button_enabled,
                                        bool find_product_button_enabled,
                                        bool put_in_basket_button_enabled,
                                        bool find_recipe_button_enabled,
                                        bool choose_recipe_button_enabled,
                                        bool check_basket_button_enabled) {
    // idk, лучше ли такая функция явного прописывания, ибо здесь нужно всегда
    // быть аккуратным с порядком поставляемых параметров, но по строкам вышло
    // выгоднее!)
    button_enabled(add_product_button, add_product_button_enabled);
    button_enabled(add_recipe_button, add_recipe_button_enabled);
    button_enabled(find_product_button, find_product_button_enabled);
    button_enabled(put_in_basket_button, put_in_basket_button_enabled);
    button_enabled(find_recipe_button, find_recipe_button_enabled);
    button_enabled(choose_recipe_button, choose_recipe_button_enabled);
    button_enabled(check_basket_button, check_basket_button_enabled);
    //обновление состояний кнопок

    //в нашей программе всегда доступны
    set_font_color_button(next_button, StyleSettings::Colors::green_button,
                          StyleSettings::FontSizes::standard_medium_button_sz,
                          true);
    set_font_color_button(previous_button, StyleSettings::Colors::green_button,
                          StyleSettings::FontSizes::standard_medium_button_sz,
                          true);
}

void RecipeBook::update_buttons_showed(bool add_product_button_showed,
                                       bool add_recipe_button_showed,
                                       bool find_product_button_showed,
                                       bool put_in_basket_button_showed,
                                       bool find_recipe_button_showed,
                                       bool choose_recipe_button_showed,
                                       bool check_basket_button_showed,
                                       bool next_button_showed,
                                       bool previous_button_showed) {
    button_showed(add_product_button, add_product_button_showed);
    button_showed(add_recipe_button, add_recipe_button_showed);
    button_showed(find_product_button, find_product_button_showed);
    button_showed(put_in_basket_button, put_in_basket_button_showed);
    button_showed(find_recipe_button, find_recipe_button_showed);
    button_showed(choose_recipe_button, choose_recipe_button_showed);
    button_showed(check_basket_button, check_basket_button_showed);
    button_showed(next_button, next_button_showed);
    button_showed(previous_button, previous_button_showed);
}

RecipeBook::RecipeBook(QWidget *parent) : QWidget(parent) {
    product_name_label =
        new QLabel(StyleSettings::Titles::product_name_label_title.c_str());
    set_font_color_label(product_name_label, StyleSettings::Colors::white,
                         StyleSettings::FontSizes::rb_label_sz, "",
                         StyleSettings::Colors::green_label);
    product_name_label->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    product_name_label->setSizePolicy(QSizePolicy::MinimumExpanding,
                                      QSizePolicy::Expanding);
    product_name_line = new QLineEdit;
    product_name_line->setMinimumHeight(
        StyleSettings::WindowSizes::product_name_line_min_height);
    product_name_line->setStyleSheet("QLineEdit { font-size: 20px;}");
    product_name_line->setReadOnly(true);

    recipe_label =
        new QLabel(StyleSettings::Titles::recipe_label_product_title.c_str());
    set_font_color_label(recipe_label, StyleSettings::Colors::white,
                         StyleSettings::FontSizes::rb_label_sz, "",
                         StyleSettings::Colors::green_label);
    recipe_label->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    recipe_label->setSizePolicy(QSizePolicy::MinimumExpanding,
                                QSizePolicy::Expanding);
    recipe_text = new QTextEdit;
    recipe_text->setFontPointSize(StyleSettings::FontSizes::recipe_text_sz);
    recipe_text->setReadOnly(true);

    //экземпляры кнопок правой панели
    add_product_button = new QPushButton(
        StyleSettings::Titles::add_product_button_title.c_str());
    add_product_button->show();

    add_recipe_button =
        new QPushButton(StyleSettings::Titles::add_recipe_button_title.c_str());
    add_recipe_button->show();

    find_product_button = new QPushButton(
        StyleSettings::Titles::find_product_button_title.c_str());
    find_product_button->hide();

    put_in_basket_button = new QPushButton(
        StyleSettings::Titles::put_in_basket_button_title.c_str());
    put_in_basket_button->hide();

    find_recipe_button = new QPushButton(
        StyleSettings::Titles::find_recipe_button_title.c_str());
    find_recipe_button->hide();
    find_recipe_mode = BasketSearchingMode;  //поиск по набранной корзине

    check_basket_button = new QPushButton(
        StyleSettings::Titles::check_basket_button_title.c_str());
    check_basket_button->show();

    choose_recipe_button = new QPushButton(
        StyleSettings::Titles::choose_recipe_button_title.c_str());
    choose_recipe_button->hide();

    //экземпляры кнопок нижней панели
    next_button =
        new QPushButton(StyleSettings::Titles::next_button_title.c_str());
    next_button->hide();

    previous_button =
        new QPushButton(StyleSettings::Titles::previous_button_title.c_str());
    previous_button->hide();

    update_buttons_enabled();

    connect(add_product_button, SIGNAL(clicked()), this,
            SLOT(add_product_func()));
    connect(add_recipe_button, SIGNAL(clicked()), this,
            SLOT(add_recipe_func()));
    connect(find_product_button, SIGNAL(clicked()), this,
            SLOT(find_product_func()));
    connect(put_in_basket_button, SIGNAL(clicked()), this,
            SLOT(put_in_basket_func()));
    connect(find_recipe_button, SIGNAL(clicked()), this,
            SLOT(find_recipe_func()));
    connect(check_basket_button, SIGNAL(clicked()), this,
            SLOT(check_basket_func()));
    connect(choose_recipe_button, SIGNAL(clicked()), this,
            SLOT(choose_recipe_func()));
    connect(next_button, SIGNAL(clicked()), this, SLOT(next_func()));
    connect(previous_button, SIGNAL(clicked()), this, SLOT(previous_func()));

    //размещение кнопок - правая часть виджета, вертикальный столбец
    QVBoxLayout *button_layout1 = new QVBoxLayout;
    button_layout1->addWidget(add_product_button, Qt::AlignTop);
    button_layout1->addWidget(add_recipe_button);
    button_layout1->addWidget(find_product_button);
    button_layout1->addWidget(put_in_basket_button);
    button_layout1->addWidget(find_recipe_button);
    button_layout1->addWidget(check_basket_button);
    button_layout1->addWidget(choose_recipe_button);
    button_layout1
        ->addStretch();  //разместить кнопки ближе к верхней части экрана

    //размещение кнопок - нижняя часть виджета
    QHBoxLayout *button_layout2 = new QHBoxLayout;
    button_layout2->addWidget(previous_button);
    button_layout2->addWidget(next_button);

    //основной макет с поисковой строкой, полем вывода, названиями полей
    QGridLayout *main_layout = new QGridLayout;
    main_layout->addWidget(product_name_label, 0, 0);
    main_layout->addWidget(product_name_line, 0, 1);
    main_layout->addWidget(recipe_label, 1, 0, Qt::AlignTop);
    main_layout->addWidget(recipe_text, 1, 1);
    main_layout->addLayout(button_layout1, 1, 2);  //вложенная компоновка:
    //добавили button_layout1 (теперь дочерний) к main_layout
    main_layout->addLayout(button_layout2, 3, 1);

    setLayout(main_layout);
    setWindowTitle(StyleSettings::Titles::windows_title.c_str());
    set_background_image(this);
    set_minimum_window_sizes(this);
}

void RecipeBook::clear_fields() {
    //очищение полей ввода
    product_name_line->clear();
    recipe_text->clear();
}

void RecipeBook::clear_fields_and_requests() {
    clear_fields();
    product_name_line->setReadOnly(true);
    recipe_text->setReadOnly(true);

    res_of_request_products.clear();
    res_of_request_recipes.clear();
}

void RecipeBook::activate_search_bar() {
    product_name_line->setReadOnly(
        false);  //отключение режима "только для чтения"
    product_name_line->setFocus(
        Qt::OtherFocusReason);  //установка фокуса ввода на product_name_line
    recipe_text->setReadOnly(false);
}

void RecipeBook::text_field_find_regime(std::string const &s) {
    product_name_line->setText(s.c_str());
    product_name_line->setReadOnly(true);  //<=> нельзя менять
    recipe_text->setReadOnly(false);       //<=> можно менять
}

void RecipeBook::add_product_func() {
    clear_fields_and_requests();
    activate_search_bar();
    find_recipe_mode = BasketSearchingMode;

    recipe_label->setText(
        StyleSettings::Titles::recipe_label_product_title.c_str());

    update_buttons_enabled(false, true, true, true, true, true, true);
    update_buttons_showed(true, false, true, false, false, false, true, false,
                          false);
}

void RecipeBook::add_recipe_func() {
    clear_fields_and_requests();
    activate_search_bar();
    find_recipe_mode = NameSearchingMode;  //режим поиска по совпадению названий

    update_buttons_enabled(true, false, true, true, true, true, true);
    update_buttons_showed(false, true, false, false, true, false, true, false,
                          false);
}

void RecipeBook::find_product_func() {
    //пустой ввод
    if (product_name_line->text() == "") {
        QMessageBox::information(
            this, StyleSettings::Titles::empty_input_window_title.c_str(),
            StyleSettings::Titles::empty_input_window_text.c_str());
        return;
    }
    text_field_find_regime(product_name_line->text().toStdString());

    update_buttons_enabled(true, true, false, true, true, true, true);
    update_buttons_showed(true, false, true, true, false, false, true, true,
                          true);

    current_mode = FindProduct_mode;
    //запуск поиска
    res_of_request_products.clear();
    res_of_request_products = API::ingredients_and_recipes::run_product_search(
                                  product_name_line->text().toStdString(),
                                  StyleSettings::FontSizes::top_products_count,
                                  res_of_request_products)
                                  .first;
    //установка полей и вывод первого продукта
    recipe_label->setText(
        StyleSettings::Titles::recipe_label_product_title.c_str());
    recipe_text->clear();
    print_product_by_name_price(recipe_text, res_of_request_products[0]);

    num_current_object = 0;
}

void RecipeBook::put_in_basket_func() {
    //добавление продукта в корзину по его номеру в массиве
    // res_of_request_products
    if (res_of_request_products.empty()) {
        return;
    }
    API::put_product_in_basket(basket_of_products,
                               res_of_request_products[num_current_object]);

    clear_fields_and_requests();

    update_buttons_enabled(true, true, true, false, true, true, true);
    update_buttons_showed(true, false, false, false, true, false, true, false,
                          false);
}

void RecipeBook::find_recipe_func() {
    if (find_recipe_mode == BasketSearchingMode) {
        //не пуста ли корзина
        if (basket_of_products.empty()) {
            res_of_request_products.clear();
            res_of_request_recipes.clear();
            QMessageBox::warning(
                this, StyleSettings::Titles::empty_basket_window_title.c_str(),
                StyleSettings::Titles::empty_basket_window_text.c_str());
            return;
        }
        text_field_find_regime(StyleSettings::Titles::was_found_title);
    } else if (find_recipe_mode == NameSearchingMode) {
        product_name_line->setReadOnly(true);
        recipe_text->setReadOnly(false);
    }

    update_buttons_enabled(true, true, true, true, false, true, true);
    update_buttons_showed(true, false, false, false, false, true, true, true,
                          true);

    current_mode = FindRecipe_mode;
    recipe_label->setText(
        StyleSettings::Titles::recipe_label_recipe_title.c_str());

    recipe_text->clear();
    res_of_request_recipes.clear();

    std::vector<search::Recipe> vec;
    if (find_recipe_mode == BasketSearchingMode) {
        res_of_request_recipes =
            API::ingredients_and_recipes::run_recipes_search(
                basket_of_products,
                StyleSettings::FontSizes::top_products_count, vec);
    } else if (find_recipe_mode == NameSearchingMode) {
        res_of_request_recipes =
            API::ingredients_and_recipes::run_recipe_search_by_str(
                product_name_line->text().toStdString(),
                StyleSettings::FontSizes::top_products_count, vec)
                .first;
    }

    print_recipe(recipe_text, res_of_request_recipes[0]);
    num_current_object = 0;
}

void RecipeBook::check_basket_func() {
    clear_fields();

    update_buttons_enabled(true, true, true, true, true, true, false);
    update_buttons_showed(true, false, false, false, true, false, true, false,
                          false);

    recipe_label->setText(
        StyleSettings::Titles::recipe_label_in_basket_title.c_str());

    //вывод корзины на экран
    print_products_vector(recipe_text, basket_of_products);
}

void RecipeBook::previous_func() {
    num_current_object--;
    if (current_mode == FindProduct_mode) {
        //циклический список продуктов
        if (num_current_object < 0) {
            num_current_object = res_of_request_products.size() - 1;
        }
        search::product prod = res_of_request_products[num_current_object];
        recipe_text->clear();
        print_product_by_name_price(recipe_text, prod);
    } else if (current_mode == FindRecipe_mode) {
        //циклический список рецептов
        if (num_current_object < 0) {
            num_current_object = res_of_request_recipes.size() - 1;
        }
        search::Recipe recipe = res_of_request_recipes[num_current_object];
        recipe_text->clear();
        print_recipe(recipe_text, recipe);
    }
}

void RecipeBook::next_func() {
    num_current_object++;
    if (current_mode == FindProduct_mode) {
        //циклический список продуктов
        if (num_current_object == res_of_request_products.size()) {
            num_current_object = 0;
        }
        search::product prod = res_of_request_products[num_current_object];
        recipe_text->clear();
        print_product_by_name_price(recipe_text, prod);
    } else if (current_mode == FindRecipe_mode) {
        //циклический список рецептов
        if (num_current_object == res_of_request_recipes.size()) {
            num_current_object = 0;
        }
        search::Recipe recipe = res_of_request_recipes[num_current_object];
        recipe_text->clear();
        print_recipe(recipe_text, recipe);
    }
}

void RecipeBook::choose_recipe_func() {
    //переход к summary_window
    API::ingredients_and_recipes::choose_recipe(num_current_object);

    auto summary_window = new SummaryWindow;
    summary_window->show();
    this->close();
}
}  // namespace Ui