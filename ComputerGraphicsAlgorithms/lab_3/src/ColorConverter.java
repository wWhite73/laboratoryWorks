import java.awt.Color;
import java.util.InputMismatchException;
import java.util.Scanner;

public class ColorConverter {

    public static float[] rgbToCmyk(int r, int g, int b) {
        float[] cmyk = new float[4];
        float c = 1 - r / 255f;
        float m = 1 - g / 255f;
        float y = 1 - b / 255f;
        float k = Math.min(c, Math.min(m, y));

        if (k == 1) {
            cmyk[0] = 0;
            cmyk[1] = 0;
            cmyk[2] = 0;
            cmyk[3] = 1;
        } else {
            cmyk[0] = (c - k) / (1 - k);
            cmyk[1] = (m - k) / (1 - k);
            cmyk[2] = (y - k) / (1 - k);
            cmyk[3] = k;
        }

        return cmyk;
    }

    public static Color cmykToRgb(float c, float m, float y, float k) {
        int r = Math.round((1 - Math.min(1, c * (1 - k) + k)) * 255);
        int g = Math.round((1 - Math.min(1, m * (1 - k) + k)) * 255);
        int b = Math.round((1 - Math.min(1, y * (1 - k) + k)) * 255);

        return new Color(r, g, b);
    }

    public static int[] rgbToYuv(int r, int g, int b) {
        r = Math.max(0, Math.min(255, r));
        g = Math.max(0, Math.min(255, g));
        b = Math.max(0, Math.min(255, b));

        int y = (int) Math.round(0.299 * r + 0.587 * g + 0.114 * b);
        int u = (int) Math.round(-0.14713 * r - 0.28886 * g + 0.436 * b + 128);
        int v = (int) Math.round(0.615 * r - 0.51498 * g - 0.10001 * b + 128);
        return new int[]{y, u, v};
    }

    public static int[] yuvToRgb(double y, double u, double v) {
        u = u - 128;  // учет смещения
        v = v - 128;  // учет смещения

        int r = (int) (y + 1.13983 * v);
        r = Math.max(0, Math.min(255, r));

        int g = (int) (y - 0.39465 * u - 0.58060 * v);
        g = Math.max(0, Math.min(255, g));

        int b = (int) (y + 2.03211 * u);
        b = Math.max(0, Math.min(255, b));

        return new int[]{r, g, b};
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int r, g, b;
        float c, m, y, k;
        double yIn, u, v;

        System.out.println("Введите значения RGB:");
        r = scanner.nextInt();
        g = scanner.nextInt();
        b = scanner.nextInt();

        float[] cmyk = rgbToCmyk(r, g, b);
        System.out.printf("CMYK: %.2f, %.2f, %.2f, %.2f\n", cmyk[0], cmyk[1], cmyk[2], cmyk[3]);

        int[] yuv = rgbToYuv(r, g, b);
        System.out.printf("YUV: %d, %d, %d\n", yuv[0], yuv[1], yuv[2]);

        System.out.println("Введите значения CMYK:");
        c = scanner.nextFloat();
        m = scanner.nextFloat();
        y = scanner.nextFloat();
        k = scanner.nextFloat();

        Color rgbFromCmyk = cmykToRgb(c, m, y, k);
        System.out.println("RGB: " + rgbFromCmyk.getRed() + ", " + rgbFromCmyk.getGreen() + ", " + rgbFromCmyk.getBlue());

        System.out.println("Введите значения YUV:");
        yIn = scanner.nextDouble();
        u = scanner.nextDouble();
        v = scanner.nextDouble();

        int[] rgbFromYuv = yuvToRgb(yIn, u, v);
        System.out.println("RGB: " + rgbFromYuv[0] + ", " + rgbFromYuv[1] + ", " + rgbFromYuv[2]);
    }
}
