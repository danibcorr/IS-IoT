# %% Librerias

import streamlit as st
from functions.data_acquisition import adquisicion_datos
from functions.data_analysis import plot_data

# %% Parametros

st.set_page_config(
    page_title = "Inicio",
    page_icon = "🍓"
)

st.title("🍓 Inicio")

# %% Funciones

def texto_inicio():

    st.markdown("""
        ## 👋 Introducción

        Bienvenidos a nuestro proyecto, que se centra en la creación de un sistema IoT basado en las tecnologías Arduino y ESP32, 
        diseñado para adquirir, manipular y visualizar datos. Nuestro objetivo principal es simular el funcionamiento de un invernadero.

        Para lograr una simulación precisa, recopilamos datos sobre varios factores ambientales críticos. Estos incluyen la temperatura, 
        la luminosidad y la humedad. Al monitorear y analizar estos factores, podemos optimizar las condiciones dentro del invernadero 
        y mejorar la eficiencia de la producción.

        ## 🛠️ Aplicación
    """)

# %% Main

if __name__ == "__main__":

    # Mostrar el mensaje de inicio
    texto_inicio()

    # Valor por defecto en Linux
    puerto = '/dev/ttyACM0'

    # Parámetros seleccionados por el usuario
    baudios = st.number_input('Introduce los baudios:')
    nombre_fichero = st.text_input('Introduce el nombre del fichero:')
    
    # Crea un botón para que el usuario elija cuando empezar a realizar la adquisición de datos
    start_button = st.button('Comenzar la adquisición de datos')

    # Si el usuario ha introducido un puerto y un directorio de archivo, llama a las funciones adquisicion_datos y plot_data
    if puerto and nombre_fichero and start_button:

        adquisicion_datos(puerto = puerto, baudios = baudios, nombre_fichero = nombre_fichero)
        plot_data(file_path)