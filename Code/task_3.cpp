// task_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

/* The class TextFormatter is an abstract base class with a pure virtual function format for formatting
text. */
class TextFormatter {
public:
    virtual void format(std::string& text) const = 0;
    virtual ~TextFormatter() {}
};

/* The class `Text` represents a text object that can be modified, formatted, and displayed. */
class Text {
private:
    std::string text;
    std::vector<TextFormatter*> formatters;
public:
    Text(const std::string& initialText = "") : text(initialText) {}

    void addText(const std::string& newText) {
        text += newText;
    }

    void editText(const std::string& newText) {
        text = newText;
    }

    void deleteText() {
        text.clear();
    }

    void applyFormatter(TextFormatter* formatter) {
        formatters.push_back(formatter);
    }

    void removeFormatter(TextFormatter* formatter) {
        formatters.erase(std::remove(formatters.begin(), formatters.end(), formatter), formatters.end());
    }

    void display() const {
        if (text.empty()) {
            std::cout << "Text is empty." << std::endl;
            return;
        }

        std::string formattedText = text;
        for (const auto* formatter : formatters) {
            formatter->format(formattedText);
        }
        std::cout << formattedText << std::endl;
    }

    std::string getText() const {
        return text;
    }
};


/* The `BoldTextFormatter` class in C++ inherits from `TextFormatter` and formats text to be displayed
in bold. */
class BoldTextFormatter : public TextFormatter {
public:
    void format(std::string& text) const override {
        text = "\033[1m" + text + "\033[0m";
    }
};

/* The `ItalicTextFormatter` class in C++ formats text to be displayed in italics using ANSI escape
codes. */
class ItalicTextFormatter : public TextFormatter {
public:
    void format(std::string& text) const override {
        text = "\033[3m" + text + "\033[0m";
    }
};

/* The UppercaseTextFormatter class is a C++ class that converts text to uppercase. */
class UppercaseTextFormatter : public TextFormatter {
public:
    void format(std::string& text) const override {
        std::string upperText = text;
        std::transform(upperText.begin(), upperText.end(), upperText.begin(), ::toupper);
        text = upperText;
    }
};

/* The LowercaseTextFormatter class is a C++ class that inherits from TextFormatter and converts text
to lowercase. */
class LowercaseTextFormatter : public TextFormatter {
public:
    void format(std::string& text) const override {
        std::string lowerText = text;
        std::transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
        text = lowerText;
    }
};

/* The LineBreakTextFormatter class is a C++ class that appends a newline character to a given text
string. */
class LineBreakTextFormatter : public TextFormatter {
public:
    void format(std::string& text) const override {
        text += "\n";
    }
};

/* The class `File` represents a file with attributes such as name, creation date, update date, and
text content. */
class File {
private:
    std::string name;
    std::time_t creationDate;
    std::time_t updateDate;
    Text* text;
public:
    File(const std::string& fileName) : name(fileName), text(new Text()) {
        creationDate = std::time(nullptr);
        updateDate = creationDate;
    }

    ~File() {
        delete text;
    }

    void saveUpdate() {
        updateDate = std::time(nullptr);
    }

    Text* getText() const {
        return text;
    }

    std::string getName() const {
        return name;
    }

    std::time_t getCreationDate() const {
        return creationDate;
    }

    std::time_t getUpdateDate() const {
        return updateDate;
    }
};

/* The TextEditor class manages a File object for editing and displaying text. */
class TextEditor {
private:
    File* file;
public:
    TextEditor() : file(nullptr) {}

    void createNewFile(const std::string& fileName) {
        file = new File(fileName);
    }

    void editText(const std::string& newText) {
        if (file) {
            file->getText()->editText(newText);
            file->saveUpdate();
        }
    }

    void displayText() const {
        if (file) {
            file->getText()->display();
        }
        else {
            std::cout << "No file is open." << std::endl;
        }
    }

    File* getFile() const {
        return file;
    }

    ~TextEditor() {
        delete file;
    }
};

int main() {
    std::cout << "=== Text Editor ===" << std::endl;

    TextEditor editor;
    editor.createNewFile("Eugene.txt");
    std::cout << "Created new file: " << editor.getFile()->getName() << std::endl;

    Text* text = editor.getFile()->getText();
    text->addText("Hello, World!");
    std::cout << "\nOriginal text: ";
    editor.displayText();

    TextFormatter* bold = new BoldTextFormatter();
    TextFormatter* lineBreak = new LineBreakTextFormatter();
    text->applyFormatter(bold);
    text->applyFormatter(lineBreak);

    std::cout << "Applied bold and line break formatters:" << std::endl;
    std::cout << "Formatted text: ";
    editor.displayText();

    TextFormatter* italic = new ItalicTextFormatter();
    text->applyFormatter(italic);

    std::cout << "Added italic formatter:" << std::endl;
    std::cout << "Formatted text: ";
    editor.displayText();

    text->removeFormatter(bold);
    TextFormatter* uppercase = new UppercaseTextFormatter();
    text->applyFormatter(uppercase);

    std::cout << "Removed bold formatter, applied uppercase formatter:" << std::endl;
    std::cout << "Formatted text: ";
    editor.displayText();

    delete bold;
    delete italic;
    delete uppercase;
    delete lineBreak;

    std::cout << "\n=== Completed ===" << std::endl;

    return 0;
}