#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Book {
    std::string id;
    std::string author;
    std::string title;
    int pages;

    void display() const {
        std::cout << "ID: " << id << "\nAuthor: " << author << "\nTitle: " << title << "\nPages: " << pages << "\n\n";
    }
};

// Функция для загрузки книг из файла в вектор
std::vector<Book> loadBooks(const std::string& filename) {
    std::vector<Book> books;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Book book;
            iss >> book.id >> book.author >> book.title >> book.pages;
            books.push_back(book);
        }
        file.close();
    }
    return books;
}

// Функция для сохранения всех книг из вектора в файл
void saveBooks(const std::string& filename, const std::vector<Book>& books) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& book : books) {
            file << book.id << " " << book.author << " " << book.title << " " << book.pages << "\n";
        }
        file.close();
    }
}

int main() {
    const std::string filename = "books.txt";
    std::vector<Book> books = loadBooks(filename);

    // Пример добавления новой записи
    Book newBook{ "0003", "J.R.R. Tolkien", "The Lord of the Rings", 1178 };
    books.push_back(newBook);

    // Пример просмотра всех записей
    for (const auto& book : books) {
        book.display();
    }

    // Пример поиска записи
    std::string searchId = "0002";
    for (const auto& book : books) {
        if (book.id == searchId) {
            std::cout << "Found Book:\n";
            book.display();
        }
    }

    // Пример удаления записи (по ID)
    for (auto it = books.begin(); it != books.end();) {
        if (it->id == "0001") {
            it = books.erase(it);
        }
        else {
            ++it;
        }
    }

    // Пример редактирования записи (по ID)
    for (auto& book : books) {
        if (book.id == "0003") {
            book.pages = 1500; // Обновляем количество страниц
        }
    }

    saveBooks(filename, books); // Сохраняем все изменения обратно в файл

    return 0;
}