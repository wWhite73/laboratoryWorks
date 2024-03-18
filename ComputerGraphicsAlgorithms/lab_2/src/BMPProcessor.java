import javax.swing.*;
import java.io.*;

public class BMPProcessor {
    public static void processBMP(File inputFile, ImagePanel panel) {
        try {
            FileInputStream fis = new FileInputStream(inputFile);
            byte[] inputBytes = new byte[(int) inputFile.length()];
            fis.read(inputBytes);
            int fileSize = getInt(inputBytes, 2);
            int dataOffset = getInt(inputBytes, 10);
            File outputFile = new File("output.bmp");
            FileOutputStream fos = new FileOutputStream(outputFile);
            fos.write(inputBytes);
            fis.close();
            fos.close();

            // Загружаем изображение в панель
            panel.setImage(outputFile);

            JOptionPane.showMessageDialog(null, "Файл успешно обработан!");

        } catch (IOException var10) {
            System.out.println("Произошла ошибка при чтении или записи файла: " + var10.getMessage());
        }
    }

    private static int getInt(byte[] bytes, int offset) {
        return (bytes[offset + 3] & 255) << 24 | (bytes[offset + 2] & 255) << 16 | (bytes[offset + 1] & 255) << 8 | bytes[offset] & 255;
    }
}
