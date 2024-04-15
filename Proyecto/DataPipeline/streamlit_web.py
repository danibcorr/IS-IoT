# %% Librerias

import streamlit as st
from data_acquisition import adquisicion_datos
from data_analysis import plot_data

# %% Main

if __name__ == "__main__":

    # Valor por defecto en Linux
    puerto = '/dev/ttyACM0'

    # Parámetros seleccionados por el usuario
    baudios = st.number_input('Introduce los baudios:')
    file_path = st.text_input('Introduce el directorio con el nombre del fichero y extensión (.csv):')
    
    # Crea un botón para que el usuario elija cuando empezar a realizar la adquisición de datos
    start_button = st.button('Comenzar la adquisición de datos')

    # Si el usuario ha introducido un puerto y un directorio de archivo, llama a las funciones adquisicion_datos y plot_data
    if puerto and file_path and start_button:

        adquisicion_datos(puerto = puerto, baudios = baudios, path_fichero = file_path)
        plot_data(file_path)