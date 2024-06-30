# 🌿 Sistema de Monitoreo Ambiental con Arduino y ESP32

## 🎓 Proyecto Final - Universidad de Málaga

Este repositorio contiene todos los documentos y código necesarios para el seguimiento, control de versiones y realización de las prácticas de la asignatura de Ingeniería del Software para Internet de las Cosas, impartida en la Universidad de Málaga (UMA) como parte del Máster en Telemática y Redes de Telecomunicación.

## 📋 Descripción del Proyecto

Este sistema de monitorización simula un entorno de invernadero, utilizando Arduino Mega y ESP32 para recopilar datos ambientales como temperatura, humedad y luminosidad. Los datos son procesados y visualizados para su análisis.

## 🔧 Funcionamiento

1. Los sensores conectados a la ESP32 recopilan datos ambientales.
2. La ESP32 envía los datos al módulo Bluetooth HC-06 de la Arduino Mega.
3. La Arduino Mega transfiere los datos a un ordenador vía conexión por cable.
4. Los datos son procesados y visualizados utilizando Python y Streamlit.

## 📊 Características

- Recopilación de datos en tiempo real
- Almacenamiento de datos en formato CSV
- Visualización de datos mediante gráficos interactivos
- Cálculo de promedios de parámetros ambientales
- Sistema de alertas para condiciones fuera de rango
- Recomendaciones para el cultivo basadas en las condiciones ambientales

## 👥 Autores

Este proyecto fue desarrollado por Daniel Bazo Correa y Laura Camacho Lara como parte del Máster en Telemática y Redes de Telecomunicación en la Escuela Técnica Superior de Ingeniería de Telecomunicación de la Universidad de Málaga.
