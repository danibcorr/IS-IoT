# %% Librerias

import pandas as pd
import plotly.express as px
import streamlit as st

# %% Funciones

def plot_data(file_path):

    # Lee los datos del archivo CSV
    df = pd.read_csv(file_path)

    # Crea la gráfica de la temperatura
    fig_temp = px.line(df, y = 'Temperatura', title = 'Temperatura')
    st.plotly_chart(fig_temp)

    # Crea la gráfica de la humedad
    fig_hum = px.line(df, y = 'Humedad', title = 'Humedad')
    st.plotly_chart(fig_hum)