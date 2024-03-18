import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;

public class LZ78BMPGUI extends JFrame {
    private static final int MAX_DICTIONARY_SIZE = 256;
    private final HashMap<String, Integer> dictionary = new HashMap<>();
    private final String[] arrayDictionary = new String[MAX_DICTIONARY_SIZE];
    private int dictSize = 1;

    // Метод для сжатия строки с использованием алгоритма LZ78
    public String compress(String uncompressed) {
        String w = "";
        StringBuilder result = new StringBuilder();

        for (char c : uncompressed.toCharArray()) {
            String wc = w + c;
            if (dictionary.containsKey(wc))
                w = wc;
            else {
                if (w.equals("")) {
                    result.append("0");
                } else {
                    result.append(dictionary.get(w));
                }
                result.append(c);
                // Добавляем wc в словарь, если он не слишком большой
                if (dictSize < MAX_DICTIONARY_SIZE) dictionary.put(wc, dictSize++);
                w = String.valueOf(c);
            }
        }

        // Выводим код для w, если это необходимо
        if (!w.equals("")) {
            if (w.length() == 1) {
                result.append("0");
                result.append(w);
            } else {
                result.append(dictionary.get(w));
            }
        }
        return result.toString();
    }

    // Метод для декомпрессии строки с использованием алгоритма LZ78
    public String decompress(String compressed) {
        String w = "";
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < compressed.length(); i += 2) {
            int k = Integer.parseInt(String.valueOf(compressed.charAt(i)));
            char c = compressed.charAt(i + 1);
            String entry;
            if (k == 0) {
                entry = String.valueOf(c);
            } else {
                entry = arrayDictionary[k] + c;
            }
            result.append(entry);

            // Добавляем wc в словарь
            if (dictSize < MAX_DICTIONARY_SIZE) arrayDictionary[dictSize++] = w + c;
            w = entry;
        }
        return result.toString();
    }

    public LZ78BMPGUI() {
        setTitle("LZ78 BMP Encoder/Decoder");
        setSize(400, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        panel.setLayout(new FlowLayout());

        JButton openButton = new JButton("Open BMP File");
        openButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                int returnValue = fileChooser.showOpenDialog(null);
                if (returnValue == JFileChooser.APPROVE_OPTION) {
                    File selectedFile = fileChooser.getSelectedFile();
                    try {
                        // Читаем BMP-файл
                        FileInputStream fis = new FileInputStream(selectedFile);
                        byte[] bytes = new byte[(int) selectedFile.length()];
                        fis.read(bytes);
                        fis.close();

                        // Преобразуем BMP-файл в 16-чную строку
                        StringBuilder sb = new StringBuilder();
                        for (byte b : bytes) {
                            sb.append(String.format("%02X ", b));
                        }
                        String hexString = sb.toString();

                        // Сжимаем 16-чную строку
                        String compressed = compress(hexString);
                        System.out.println("Сжатые данные: " + compressed);

                        // Записываем сжатые данные в файл
                        File compressedFile = new File("./compressed.bmp");
                        try (PrintWriter out = new PrintWriter(compressedFile)) {
                            out.println(compressed);
                        }

                        // Читаем сжатые данные из файла
                        String readCompressed;
                        try (Scanner scanner = new Scanner(compressedFile)) {
                            readCompressed = scanner.nextLine();
                        }

                        // Декомпрессируем сжатую строку
                        String decompressed = decompress(readCompressed);
                        System.out.println("Декомпрессированные данные: " + decompressed);

                        // Преобразуем декомпрессированную строку обратно в байты
                        String[] hexBytes = decompressed.split(" ");
                        byte[] decompressedBytes = new byte[hexBytes.length];
                        for (int i = 0; i < hexBytes.length; i++) {
                            decompressedBytes[i] = (byte) Integer.parseInt(hexBytes[i], 16);
                        }

                        // Записываем декомпрессированные байты обратно в BMP-файл
                        File decompressedFile = new File("./decompressed.bmp");
                        FileOutputStream fos = new FileOutputStream(decompressedFile);
                        fos.write(decompressedBytes);
                        fos.close();
                    } catch (IOException ex) {
                        ex.printStackTrace();
                    }
                }
            }
        });
        panel.add(openButton);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                LZ78BMPGUI frame = new LZ78BMPGUI();
                frame.setVisible(true);
            }
        });
    }
}
