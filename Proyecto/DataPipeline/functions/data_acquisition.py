# %% Librerias

import serial
import streamlit as st
import pandas as pd

# %% Funciones

def adquisicion_datos(puerto, baudios, nombre_fichero):
    
    ser = serial.Serial(puerto, baudios) 

    # Crear una lista vacía para almacenar los datos
    data = []

    try:

        while True:
        
            if ser.in_waiting > 0:
        
                # Leer una línea de datos desde el puerto serie
                linea = ser.readline().decode('utf-8').rstrip()
                
                # Si la línea es "Comunicacion cortada", terminar la adquisición de datos
                if linea == "Comunicacion cortada":

                    print("Comunicacion cortada")
                    break

                # Dividir la línea en humedad, temperatura y luminosidad
                humedad, temperatura, luminosidad = linea.split(',')

                # Limpiar y convertir los valores a flotantes
                humedad = float(humedad.split(':')[1].strip().replace('%', ''))
                temperatura = float(temperatura.split(':')[1].strip().replace('°C', ''))
                luminosidad = float(luminosidad.split(':')[1].strip())

                # Agregar los valores a la lista de datos
                data.append({'Humedad': humedad, 'Temperatura': temperatura, 'Luminosidad': luminosidad})

                # Imprimir los valores recibidos
                print(f'Humedad: {humedad}, Temperatura: {temperatura}, Luminosidad: {luminosidad}')

    except KeyboardInterrupt:

        print("Interrupción del usuario. Cerrando el puerto serie...")
        
    finally:
        
        # Crear un DataFrame de pandas a partir de la lista de datos
        df = pd.DataFrame(data)
        
        # Guardar el DataFrame en un archivo CSV
        file_path = "./dataset/" + nombre_fichero + ".csv"
        df.to_csv(file_path, index = False)
        print(f"Datos guardados en '{file_path}'")
        
        # Cerramos el puerto serie
        ser.close()  
