import javax.swing.*;
import java.awt.*;




public class BMPApp extends JFrame {
    public BMPApp() {
        JPanel panel = new JPanel();
        panel.setDropTarget(new FileDropTarget());
        add(panel, BorderLayout.CENTER);
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(BMPApp::new);
    }
}
