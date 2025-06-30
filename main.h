#ifndef MAIN_H
#define MAIN_H

#include <QColor>
#include <QDateTime>
#include <QList>
#include <QString>
#include <QJsonDocument>

enum class ApiResult {
    Success,
    NetworkError,
    InvalidApiKey,
    NotFound
};

ApiResult fetchWeatherMock(const QString& url);


/**
 * @struct WeatherPoint
 * @brief Хранит данные о погоде в конкретный момент времени.
 */
struct WeatherPoint {
    QDateTime datetime;    ///< Дата и время измерения
    double temperature;    ///< Температура в градусах Цельсия
    double pressure;       ///< Атмосферное давление в hPa
    double humidity;       ///< Относительная влажность в процентах
    double windspeed;      ///< Скорость ветра в метрах в секунду
};

/**
 * @brief Определяет цвет фона в зависимости от температуры.
 *
 * @param temp_c Температура в градусах Цельсия.
 * @return QColor Цвет для подложки.
 */
QColor fon(double temp_c);

/**
 * @brief Парсит JSON с погодой от VisualCrossing.
 *
 * @param doc   JSON-документ (QJsonDocument) с данными API.
 * @param freq  Частота данных: "1h", "3h", "6h", "12h", "1d".
 * @return QList<WeatherPoint> Список точек погоды по расписанию.
 */
QList<WeatherPoint> parseVisualCrossingJson(const QJsonDocument& doc, const QString& freq);

#endif // MAIN_H
