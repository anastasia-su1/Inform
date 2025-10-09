#include <SFML/Graphics.hpp> 
#include <functional> 
#include <cmath> 

// Функция для отрисовки графика
void drawGraph(sf::RenderWindow& window, std::function<float(float)> func, float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);

    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x); // Вычисление значения функции

        // Преобразование координат в экранные
        float screenX = 400 + x * scaleX;
        float screenY = 400 - y * scaleY;

        // Добавление точки в массив вершин
        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }

    window.draw(graph);
}

int main() {


    // Создание окна
    sf::RenderWindow window(sf::VideoMode(800, 800), L"Приложение для вывода графиков");

    // Переменная для хранения пользовательской точки
    sf::CircleShape userPoint(5); // Радиус 5 пикселей
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false; // Переменная для проверки существования пользовательской точки

    // Загрузка шрифта
    sf::Font font;
    if (!font.loadFromFile("CyrilicOld.ttf")) {
        return -1;
    }

    // Текст для отображения координат точки
    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setFillColor(sf::Color::White);
    coordinatesText.setPosition(10, 10);

    // Оси X и Y
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(50, 400); // Начало оси X
    xAxis[0].color = sf::Color::White; // Цвет оси
    xAxis[1].position = sf::Vector2f(750, 400); // Конец оси X
    xAxis[1].color = sf::Color::White;

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 50); // Начало оси Y
    yAxis[0].color = sf::Color::White; // Цвет оси
    yAxis[1].position = sf::Vector2f(400, 750); // Конец оси Y
    yAxis[1].color = sf::Color::White;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Проверка клика мышью
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Получение позиции клика
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Преобразование экранных координат в "математические"
                    float mathX = (mousePos.x - 400) / 30.0f;
                    float mathY = -(mousePos.y - 400) / 10.0f;

                    // Установка новой пользовательской точки
                    userPoint.setPosition(mousePos.x - userPoint.getRadius(), mousePos.y - userPoint.getRadius());
                    userPointExists = true; // Помечаем, что точка существует


                    // Логика проверки точки по переменным mathX и mathY !
                    if ((mathY == - 3 * mathX + 1) || (mathY == 2 * mathX - 1)){
                        coordinatesText.setString("Координаты: (" + std::to_string(mathX) + ", " + std::to_string(mathY) + "), Граница");
                     }
                    else {
                        if ((mathY > -3 * mathX + 1) && (mathY > 2 * mathX - 1)) {
                            coordinatesText.setString("Координаты: (" + std::to_string(mathX) + ", " + std::to_string(mathY) + "), Номер Зоны: 3");
                        }
                        else {
                            if ((mathY > -3 * mathX + 1) && (mathY < 2 * mathX - 1)) {

                                coordinatesText.setString("Координаты: (" + std::to_string(mathX) + ", " + std::to_string(mathY) + "), Номер Зоны: 1");
                            }
                            else {
                                if ((mathY < -3 * mathX + 1) && (mathY < 2 * mathX - 1)) {
                                    coordinatesText.setString("Координаты: (" + std::to_string(mathX) + ", " + std::to_string(mathY) + "), Номер Зоны: 2");
                                }
                                else {
                                    if ((mathY < -3 * mathX + 1) && (mathY > 2 * mathX - 1)) {
                                        coordinatesText.setString("Координаты: (" + std::to_string(mathX) + ", " + std::to_string(mathY) + "), Номер Зоны: 4");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        window.clear();

        // Отрисовка осей
        window.draw(xAxis);
        window.draw(yAxis);



        // 5 _  Отрисовка графика y1 = 2 * x - 1
        drawGraph(window, [](float x) { return 2 * x - 1; }, -10, 10, 30, 10, sf::Color::Blue);

        // 5 _   Отрисовка графика y2 = -3 * x + 1
        drawGraph(window, [](float x) { return -3 * x + 1; }, -10, 10, 30, 10, sf::Color::Red);

        // Отрисовка пользовательской точки, если она существует
        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
        }

        // Отображение нового кадра
        window.display();
    }

    return 0;
}