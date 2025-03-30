#include "crow_all.h"
#include <fstream>
#include <sstream>
#include <vector>

// Hardcoded login credentials
const std::string USERNAME = "carter";
const std::string PASSWORD = "blackie";

int main() {
    crow::SimpleApp app;

    // Root route: Serves homepage
    CROW_ROUTE(app, "/")([](crow::response& res){
        std::ifstream in("public/index.html");
        if (in) {
            std::ostringstream contents;
            contents << in.rdbuf();
            res.write(contents.str());
        } else {
            res.code = 404;
            res.write("404 - index.html not found");
        }
        res.end();
    });

    // Route to serve images (e.g., product images)
    CROW_ROUTE(app, "/get_image/<string>")([](crow::response& res, std::string filename){
        std::ifstream in("public/images/" + filename, std::ios::binary);
        if (in) {
            std::ostringstream contents;
            contents << in.rdbuf();
            res.set_header("Content-Type", "image/png");
            res.write(contents.str());
        } else {
            res.code = 404;
            res.write("Image not found");
        }
        res.end();
    });

    // Route to serve detailed HTML pages for each product
    CROW_ROUTE(app, "/product/<int>")([](crow::response& res, int id){
        std::ifstream in("public/product" + std::to_string(id) + ".html");
        if (in) {
            std::ostringstream contents;
            contents << in.rdbuf();
            res.set_header("Content-Type", "text/html");
            res.write(contents.str());
        } else {
            res.code = 404;
            res.write("Product not found");
        }
        res.end();
    });

    // Adds a product with specified quantity to the shopping cart
    CROW_ROUTE(app, "/cart/add/<int>/<string>")([](int id, std::string qty){
        std::ofstream cartFile("cart.txt", std::ios::app);
        cartFile << "Product ID: " << id << " Quantity: " << qty << "\n";
        return "Added to cart.";
    });

    // Serves checkout page and returns HTTP 402 (Payment Required)
    CROW_ROUTE(app, "/checkout")([](crow::response& res){
        res.code = 402;
        std::ifstream in("public/checkout.html");
        if (in) {
            std::ostringstream contents;
            contents << in.rdbuf();
            res.set_header("Content-Type", "text/html");
            res.write(contents.str());
        } else {
            res.code = 404;
            res.write("Checkout page not found");
        }
        res.end();
    });

    // Route to authenticate user login
    CROW_ROUTE(app, "/login")([](const crow::request& req, crow::response& res){
        auto username = req.url_params.get("username");
        auto password = req.url_params.get("password");

        if(username && password && username == USERNAME && password == PASSWORD){
            res.code = 202; // HTTP 202 Accepted
            res.write("Login successful.");
        } else {
            res.code = 401; // HTTP 401 Unauthorized
            res.write("Unauthorized");
        }
        res.end();
    });

    // Retrieves shopping cart contents in JSON format
    CROW_ROUTE(app, "/cart_data")([](crow::response& res) {
        std::ifstream cartFile("cart.txt");
        if (cartFile) {
            crow::json::wvalue result;
            std::string line;
            int idx = 0;

            while (getline(cartFile, line)) {
                int id, qty;
                sscanf(line.c_str(), "Product ID: %d Quantity: %d", &id, &qty);

                result["cart"][idx]["id"] = id;
                result["cart"][idx]["qty"] = qty;
                idx++;
            }

            res.write(result.dump());
        } else {
            res.code = 404;
            res.write("Cart file not found");
        }
        res.end();
    });

    // Confirms the purchase and returns cart details as plain text
    CROW_ROUTE(app, "/confirm_purchase")([](crow::response& res){
        std::ifstream cartFile("cart.txt");
        if (cartFile) {
            std::ostringstream contents;
            contents << cartFile.rdbuf();
            res.set_header("Content-Type", "text/plain");
            res.write(contents.str());
        } else {
            res.code = 404;
            res.write("Cart file not found");
        }
        res.end();
    });

    // Clears the cart after successful purchase
    CROW_ROUTE(app, "/clear_cart").methods(crow::HTTPMethod::POST)([](crow::response& res){
        std::ofstream cartFile("cart.txt", std::ofstream::trunc);
        cartFile.close();
        res.write("Cart cleared.");
        res.end();
    });

    // Run webserver
    app.port(8080).multithreaded().run();
    return 0;
}
