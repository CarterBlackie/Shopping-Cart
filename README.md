# C++ Crow Web Server – Shopping Cart Simulation

This project was developed as part of a school programming assignment to demonstrate practical skills in **web development using C++** with the **Crow framework**. It simulates a basic online shopping experience with routes for product browsing, cart management, and user authentication.

---

## Overview

The application acts as a lightweight web server built with **Crow**, a modern C++ microframework for web development. It serves static HTML files, handles image requests, and processes basic e-commerce operations such as adding items to a cart, checking out, and confirming purchases.

All data is stored locally using simple text files for demonstration purposes.

---

## Key Features

- **Homepage Serving** – Serves an `index.html` file from the `/public` directory.  
- **Image Handling** – Dynamically serves product images from `/public/images`.  
- **Product Pages** – Loads product-specific HTML pages via route `/product/<id>`.  
- **Shopping Cart System** –  
  - Add items: `/cart/add/<id>/<qty>`  
  - View cart: `/cart_data` (returns JSON)  
  - Clear cart: `/clear_cart` (HTTP POST request)  
- **Checkout and Purchase Confirmation** –  
  - `/checkout` serves the checkout page and returns HTTP 402 (Payment Required).  
  - `/confirm_purchase` displays all items in the cart as plain text.  
- **User Authentication** – Simple login endpoint `/login` using hardcoded credentials.

---

## Credentials
These were hard coded due to the nature of the assignment

const std::string USERNAME = "carter";
const std::string PASSWORD = "blackie";


****
