#include <iostream>
#include <string>
#include <Windows.h>
#include <opencv2/opencv.hpp>

// Función para abrir el explorador de archivos y obtener la ruta de un archivo de video
std::wstring obtenerRutaVideo() {
    OPENFILENAMEW ofn;
    wchar_t szFile[MAX_PATH] = L"";

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = L"Videos (*.mp4)\0*.mp4\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrTitle = L"Seleccionar video";
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if (GetOpenFileNameW(&ofn)) {
        return std::wstring(ofn.lpstrFile);
    }
    else {
        return L"";
    }
}

int main() {
    // Obtener la ruta del video
    std::wstring rutaVideo = obtenerRutaVideo();
    if (rutaVideo.empty()) {
        std::wcout << L"No se seleccionó un archivo de video." << std::endl;
        return 0;
    }

    // Convertir la ruta del video a cadena de caracteres estándar
    std::string rutaVideoStr(rutaVideo.begin(), rutaVideo.end());

    // Abrir el archivo de video
    cv::VideoCapture video(rutaVideoStr);
    if (!video.isOpened()) {
        std::cout << "No se pudo abrir el archivo de video." << std::endl;
        return 0;
    }

    // Reproducir el video
    cv::Mat frame;
    cv::namedWindow("Video", cv::WINDOW_NORMAL);
    cv::resizeWindow("Video", 640, 480);

    while (true) {
        if (!video.read(frame))
            break;

        cv::imshow("Video", frame);

        if (cv::waitKey(30) == 27)
            break;
    }

    // Liberar recursos
    video.release();
    cv::destroyAllWindows();

    return 0;
}
