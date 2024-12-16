#include "predict.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>

predict::predict(QObject *parent)
    : QObject{parent}
{
    pythonPath = "D:\\path\\conda\\python.exe";

}

void predict::callModel(const QString &scriptPath, const QList<float> &ax, const QList<float> &ay, const QList<float> &az)
{
    // Create a QProcess to run the Python script
    QProcess process;

    // Convert QList<float> to QList<QVariant> (needed for JSON conversion)
    QList<QVariant> axVariantList, ayVariantList, azVariantList;
    for (float val : ax) axVariantList.append(QVariant(val));
    for (float val : ay) ayVariantList.append(QVariant(val));
    for (float val : az) azVariantList.append(QVariant(val));

    // Create JSON object to hold the input data
    QJsonObject inputJson;
    inputJson["ax"] = QJsonArray::fromVariantList(axVariantList);
    inputJson["ay"] = QJsonArray::fromVariantList(ayVariantList);
    inputJson["az"] = QJsonArray::fromVariantList(azVariantList);

    // Convert the input JSON object to a JSON string
    QString inputString = QJsonDocument(inputJson).toJson(QJsonDocument::Compact);

    // Prepare the arguments for the Python script
    QString pythonPath = "python"; // Replace with the correct Python interpreter path if necessary
    QStringList argument;
    argument << scriptPath << inputString;  // Pass the script path and the JSON data as argument

    // Start the Python script with arguments
    process.start(pythonPath, argument);

    // Wait for the script to finish execution
    if (!process.waitForFinished()) {
        qDebug() << "Python script execution failed:" << process.errorString();
        return;
    }

    // Get the output from the Python script
    QString output = process.readAllStandardOutput().trimmed();
    qDebug() << "Python Output:" << output;

    // Parse the output JSON
    QJsonDocument outputJson = QJsonDocument::fromJson(output.toUtf8());
    if (outputJson.isNull()) {
        qDebug() << "Failed to parse JSON output from Python.";
        return;
    }

    QJsonObject result = outputJson.object();
    QJsonArray predictions = result["predictions"].toArray();

    // Print the predictions
    qDebug() << "Predictions:";
    for (const auto& prediction : predictions) {
        qDebug() << prediction.toString();
    }
}

