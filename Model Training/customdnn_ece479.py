import numpy as np
import pandas as pd
import tensorflow as tf
import os
from sklearn.model_selection import train_test_split
from tensorflow.keras.utils import to_categorical
from tensorflow.keras.models import Sequential, load_model
from tensorflow import keras
from keras import layers
import cv2
from PIL import Image
import matplotlib.pyplot as plt
import time
import datetime
from tqdm import tqdm
import kagglehub

gtsrb_path = kagglehub.dataset_download('meowmeowmeowmeowmeow/gtsrb-german-traffic-sign')
print(gtsrb_path)

data = []
labels = []
classes = 43
cur_path = os.getcwd()
for i in (range(classes)):
    path = os.path.join('/kaggle/input/gtsrb-german-traffic-sign','train',str(i))
    images = os.listdir(path)

    for a in images:
        try:
            image = Image.open(path + '/'+ a)
            image = image.resize((32,32))
            image = np.array(image)
            data.append(image)
            labels.append(i)
        except:
            print("Error loading image")

data = np.array(data)
labels = np.array(labels)

data = data.astype('float32') / 255.0
print(data.shape, labels.shape)

X_train, X_test, y_train, y_test = train_test_split(data, labels, test_size=0.2, random_state=42)

print(X_train.shape, X_test.shape, y_train.shape, y_test.shape)

y_train = to_categorical(y_train, 43)
y_test = to_categorical(y_test, 43)

model = Sequential([
    keras.Input(shape=(32, 32, 3)),
    layers.Conv2D(filters=32, kernel_size=(5, 5), strides=(1, 1), padding='valid', activation='relu', name="CONV1"),
    layers.MaxPooling2D(pool_size=(2, 2), strides=(2, 2), name="POOLING1"),
    layers.Conv2D(filters=32, kernel_size=(5, 5), strides=(1, 1), padding='valid', activation='relu', name="CONV2"),
    layers.MaxPooling2D(pool_size=(2, 2), strides=(2, 2), name="POOLING2"),
    layers.Flatten(),
    layers.Dense(64, activation='relu', name="FULLY1"),
    layers.Dense(43, activation='softmax', name="FULLY2"),
])

model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
model.weights
model.summary()

with tf.device('/GPU:0'):
    epochs = 30
    history1 = model.fit(X_train, y_train, batch_size=128, epochs=epochs, validation_data=(X_test, y_test))

plt.figure()
plt.plot(history1.history['accuracy'], label='train', color='blue')
plt.plot(history1.history['val_accuracy'], label='validation', color='orange')
plt.title('Accuracy')
plt.xlabel('Epoch')
plt.ylabel('Accuracy')
plt.legend()
plt.show()

plt.figure()
plt.plot(history1.history['loss'], label='train', color='blue')
plt.plot(history1.history['val_loss'], label='validation', color='orange')
plt.title('Loss')
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.legend()
plt.show()


########This Code Section Not Mine, Took this Code Block from Kaggle for Using Testing Dataset Properly########
from sklearn.metrics import accuracy_score

y_test = pd.read_csv('../kaggle/input/gtsrb-german-traffic-sign/Test.csv')

labels = y_test["ClassId"].values
imgs = y_test["Path"].values

data=[]

with tf.device('/GPU:0'):
    for img in imgs:
        image = Image.open('../kaggle/input/gtsrb-german-traffic-sign/'+img)
        image = image.resize([32, 32])
        data.append(np.array(image))

X_test=np.array(data)

with tf.device('/GPU:0'):
    t0 = time.time()
    preds = np.argmax(model.predict(X_test, batch_size=128, verbose=1), axis=-1)
    t1 = time.time()

acc = accuracy_score(labels, preds)
print(f"Accuracy: {acc:.4f}")

total_time = t1 - t0
num_images = X_test.shape[0]
avg_time_per_image = (total_time / num_images) * 1000

print(f"Total inference time for {num_images} images: {total_time:.2f} seconds")
print(f"Average inference time per image: {avg_time_per_image:.4f} ms")

########################################################################################

model.save('traffic_classifier.keras')