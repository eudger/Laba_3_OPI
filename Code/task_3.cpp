// task_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

/**
 * @class TextElement
 * @brief Abstract base class for text elements.
 */
class TextElement {
public:
    virtual void display() const = 0;
    virtual std::string getText() const = 0;
    virtual ~TextElement() {}
};

/**
 * @class SimpleText
 * @brief A specific component representing plain text.
 */
class SimpleText : public TextElement {
private:
    std::string text;
public:
    SimpleText(const std::string& t) : text(t) {}
    void display() const override {
        std::cout << text;
    }
    std::string getText() const override {
        return text;
    }
};

/**
 * @class TextDecorator
 * @brief Basic decorator for text elements.
 */
class TextDecorator : public TextElement {
protected:
    TextElement* element;
public:
    TextDecorator(TextElement* el) : element(el) {}
    void display() const override {
        element->display();
    }
    std::string getText() const override {
        return element->getText();
    }
    // The destructor no longer deletes element
    virtual ~TextDecorator() {}
};

/**
 * @class UpperCaseDecorator
 * @brief Decorator for converting text to uppercase.
 */
class UpperCaseDecorator : public TextDecorator {
public:
    UpperCaseDecorator(TextElement* el) : TextDecorator(el) {}
    void display() const override {
        std::string upperText = getText();
        std::transform(upperText.begin(), upperText.end(), upperText.begin(), ::toupper);
        std::cout << upperText;
    }
};

/**
 * @class LowerCaseDecorator
 * @brief Decorator for converting text to lowercase.
 */
class LowerCaseDecorator : public TextDecorator {
public:
    LowerCaseDecorator(TextElement* el) : TextDecorator(el) {}
    void display() const override {
        std::string lowerText = getText();
        std::transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
        std::cout << lowerText;
    }
};

/**
 * @class NewLineDecorator
 * @brief Decorator for adding a newline character at the end of text.
 */
class NewLineDecorator : public TextDecorator {
public:
    NewLineDecorator(TextElement* el) : TextDecorator(el) {}
    void display() const override {
        element->display();
        std::cout << std::endl;
    }
};

/**
 * @brief Entry point for the program to showcase the work of decorators.
 */
int main() {
    TextElement* text = new SimpleText("Hello, World!");
    TextElement* upperText = new UpperCaseDecorator(text);
    TextElement* lowerText = new LowerCaseDecorator(text);
    TextElement* newLineText = new NewLineDecorator(text);
    // Create a separate object for uppercase with a new line
    TextElement* innerUpperText = new UpperCaseDecorator(text);
    TextElement* upperNewLineText = new NewLineDecorator(innerUpperText);

    std::cout << "Original: ";
    text->display();
    std::cout << "\nUppercase: ";
    upperText->display();
    std::cout << "\nLowercase: ";
    lowerText->display();
    std::cout << "\nWith New Line: ";
    newLineText->display();
    std::cout << "Uppercase with New Line: ";
    upperNewLineText->display();

    // Correctly deleting objects
    delete upperNewLineText;
    delete innerUpperText; // Deleting an internal object
    delete newLineText;
    delete lowerText;
    delete upperText;
    delete text;

    return 0;
}