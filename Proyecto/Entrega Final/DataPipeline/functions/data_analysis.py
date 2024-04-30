# %% Librerias

import pandas as pd
import plotly.express as px
import streamlit as st

# %% Funciones

def plot_data(file_path):

    # Lee los datos del archivo CSV
    df = pd.read_csv(file_path)

    st.subheader("Media de los parámetos ambientales")
    # Calcula la media de la temperatura, humedad y luminosidad
    mean_temp = df['Temperatura'].mean()
    mean_hum = df['Humedad'].mean()
    mean_lum = df['Luminosidad'].mean()

    # Muestra la media de la temperatura
    st.write("Media de Temperatura:", mean_temp)

    # Muestra la media de la humedad
    st.write("Media de Humedad:", mean_hum)

    # Muestra la media de la luminosidad
    st.write("Media de Luminosidad:", mean_lum)

    # Crea la gráfica de la temperatura
    fig_temp = px.line(df, y = 'Temperatura', title = 'Temperatura')
    st.plotly_chart(fig_temp)

    # Crea la gráfica de la humedad
    fig_hum = px.line(df, y = 'Humedad', title = 'Humedad')
    st.plotly_chart(fig_hum)

    # Crea la gráfica de la luminosidad
    fig_lum = px.line(df, y = 'Luminosidad', title = 'Luminosidad')
    st.plotly_chart(fig_lum)

    # Alertas y Notificaciones
    st.subheader("Alertas y Notificaciones")
    if mean_temp > 30:
        st.error("¡Temperatura alta detectada!")
    elif mean_hum > 80:
        st.warning("Humedad alta detectada")

    # Recomendaciones de Cultivo
    st.subheader("Recomendaciones de Cultivo")
    if mean_temp > 25 and mean_hum > 60:
        st.write("Dadas las condiciones actuales del invernadero, se recomienda cultivar tomates.")
    elif mean_temp < 20 and mean_hum < 50:
        st.write("Dadas las condiciones actuales del invernadero, se recomienda cultivar lechugas.")
    else:
        st.write("No hay recomendaciones específicas en este momento.")
