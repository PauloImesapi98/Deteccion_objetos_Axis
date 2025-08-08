*Copyright (C) 2021, Axis Communications AB, Lund, Sweden. All Rights Reserved.*

# Aplicación Detección de Obejtos Axis

## Resumen

En este repositorio se desarrolla una análitica de detección de objetos para cámaras Axis, en concreto, para cámaras con chip Artpec 7. Se usa un modelo Mobinet SSD v2 para la detección de objetos. Las detecciones se guardan en el archivo temporal /tmp para usos futuros.

## Prerequisitos

- Axis camera equipped with CPU.
- [Docker](https://docs.docker.com/get-docker/)
- Visual Studio Code con la la extensión **Dev Container** instalado.
- Git

## Instrucciones de uso

Para la ejecución de este programa se tienen que seguir los siguientes pasos:

1. Abre Visual Studio Code, y clona el repositorio. Luego ejecuta el comando 'Dev container: Reopen in container' desde la paleta de comandos.

2. Ejecuta el comando:
    ```sh
    cp /workspaces/Deteccion_objetos_Axis/app/* /opt/app/
    ```

3. Ejecuta el comando:
    ```sh
    cd /opt/app
    ```

4. Ejecuta el comando:
    ```sh
    . /opt/axis/acapsdk/environment-setup*
    ```

5. Ejecuta el comando:
    ```sh
    acap-build -a 'label/labels.txt' -a 'model/converted_model.tflite'
    ```

6. Encuentra el archivo `.eap`.
    Ejecuta el comando desde la terminal del equipo:
    ```sh
    docker cp {id_contenedor}:/opt/app/Deteccion_objetosAPI__1_0_0_armv7hf.eap /home/pmjuarezm/Documentos/
    ```

7. Instala la aplicación desde la inetrfaz web de la cámara.

8. Revisa los logs de la aplicación.

## Diseño de la aplicación

Se ha tomado como base el ejemplo [Object_detection](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/main/object-detection) del repositorio acap-native-sdk-examples de Axis.

En este proyecto, el flujo de vídeo original tiene una resolución de 800x600, mientras que **MobileNet SSD COCO** requiere una entrada de 300×300.

Por ello, se configuran dos flujos distintos:

- Uno para alimentar el modelo MobileNet.
- Otro para recortar imágenes JPG de alta resolución.

### Configuración del flujo para MobileNet

Para obtener la resolución correcta, se utilizan dos métodos:

1. **chooseStreamResolution**  
   Selecciona el flujo más pequeño y asigna sus valores a `streamWidth` y `streamHeight`.

2. **createImgProvider**  
   Devuelve un proveedor de imágenes (`ImgProvider`) con el formato de salida especificado.

### Configuración del flujo de recorte

Se utiliza la resolución original (`args.raw_width` × `args.raw_height`) para generar recortes en alta resolución.

### Configuración de la interfaz Larod

Se establece la conexión con **larod**, seleccionando el hardware y asignando los tensores de entrada y salida a archivos temporales en `/tmp`.

### Obtención de un fotograma e inferencia

- Se recupera el último fotograma disponible en formato NV12.
- Se convierte a formato RGB intercalado.
- Se envía al modelo para obtener predicciones.
- Si la puntuación supera el umbral definido, el recorte correspondiente se guarda como imagen JPG en `/tmp`.

---

## Instalación

Para instalar la aplicación, sube el archivo `.eap` a la cámara mediante su interfaz web:  
`Configuración → Aplicaciones → Agregar → Seleccionar archivo → Instalar`.

---

## Ejecución

En la vista de aplicaciones de la cámara:

1. Pulsa sobre el icono de la aplicación ACAP.
2. En la ventana emergente, pulsa **Start** para iniciar el algoritmo.

Se puede consultar el registro desde la interfaz web (**App log**) o por SSH con:

```sh
tail -f /var/volatile/log/info.log | grep object_detection
```

---

## Salida

- El modelo **MobileNet SSD v2** (COCO) genera cuatro salidas: número de detecciones, clases, puntuaciones y ubicaciones \[top, left, bottom, right\].
- Las imágenes con puntuaciones superiores al umbral se guardan en `/tmp` en formato JPG.
- Actualmente, las imágenes se sobrescriben de forma continua.

Ejemplo de salida en logs:

```sh
[ INFO    ] object_detection[645]: Object 1: Classes: 2 car - Scores: 0.769531 - Locations: [0.750146,0.086451,0.894765,0.299347]
```

---

## Licencia

**[Apache License 2.0](app/LICENSE)**
