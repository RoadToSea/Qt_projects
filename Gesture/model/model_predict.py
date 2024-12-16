import sys
import json
import numpy as np
import pandas as pd
from tensorflow.keras.models import load_model
import joblib

from sklearn.preprocessing import StandardScaler, LabelEncoder
import joblib

# 创建并保存 scaler 和 label_encoder
scaler = StandardScaler()
label_encoder = LabelEncoder()

# 保存到文件
joblib.dump(scaler, './runs/scaler.save')
joblib.dump(label_encoder, './runs/label_encoder.save')



def main():
    # 测试用例：当未提供命令行参数时使用
    test_input_data = {
        "ax": [0.1, 0.2, 0.3, 0.4, 0.5] * 10,  # 确保长度 >= 50
        "ay": [0.1, 0.1, 0.2, 0.2, 0.3] * 10,
        "az": [9.8, 9.7, 9.8, 9.9, 9.8] * 10
    }

    # 从命令行接收 JSON 数据或使用测试数据
    if len(sys.argv) < 2:
        print("No input data provided. Using test case for demonstration.")
        input_data = test_input_data
    else:
        try:
            input_data = json.loads(sys.argv[1])  # 解析命令行 JSON 数据
        except json.JSONDecodeError as e:
            print(f"Error decoding JSON input: {e}")
            sys.exit(1)

    # 提取输入数据
    ax = input_data.get("ax", [])
    ay = input_data.get("ay", [])
    az = input_data.get("az", [])
    
    if not (ax and ay and az):
        print("Invalid or missing input data.")
        sys.exit(1)

    if len(ax) < 50 or len(ay) < 50 or len(az) < 50:
        print("Insufficient data for prediction. At least 50 samples are required.")
        sys.exit(1)
    
    try:
        # 加载模型和预处理器
        scaler = joblib.load('./runs/scaler.save')
        label_encoder = joblib.load('./runs/label_encoder.save')
        model = load_model('./runs/trained_model.h5')
    except Exception as e:
        print(f"Error loading resources: {e}")
        sys.exit(1)

    try:
        # 数据预处理和预测
        new_data = pd.DataFrame({'ax': ax, 'ay': ay, 'az': az})
        X_new_raw = new_data[['ax', 'ay', 'az']].values
        X_new_scaled = scaler.transform(X_new_raw)
        X_new = create_windows_predict(X_new_scaled, window_size=50, step=25)
        
        if X_new.shape[0] == 0:
            print("No valid windows created for prediction.")
            sys.exit(1)
        
        predictions = model.predict(X_new)
        predicted_classes = np.argmax(predictions, axis=1)
        predicted_labels = label_encoder.inverse_transform(predicted_classes)
        print(json.dumps({"predictions": predicted_labels.tolist()}))
    except Exception as e:
        print(f"Prediction error: {e}")
        sys.exit(1)

def create_windows_predict(data, window_size=100, step=50):
    num_samples = ((len(data) - window_size) // step) + 1
    if num_samples <= 0:
        return np.empty((0, window_size, data.shape[1]))
    X = np.zeros((num_samples, window_size, data.shape[1]))
    for i in range(num_samples):
        start = i * step
        end = start + window_size
        X[i] = data[start:end]
    return X

if __name__ == "__main__":
    main()
