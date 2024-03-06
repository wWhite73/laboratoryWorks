import java.util.*;
import java.io.*;

public class LZ78 {
    private final HashMap<Integer, String> dictionary = new HashMap<>();
    private int dictSize = 1;

    public LZ78() {
        dictionary.put(0, "");
    }

    public ArrayList<Pair<Integer, Character>> encode(String data) {
        ArrayList<Pair<Integer, Character>> encodedData = new ArrayList<>();
        String s = "";
        for (char c : data.toCharArray()) {
            if (dictionary.containsValue(s + c)) {
                s = s + c;
            } else {
                for (Map.Entry<Integer, String> entry : dictionary.entrySet()) {
                    if (Objects.equals(entry.getValue(), s)) {
                        encodedData.add(new Pair<>(entry.getKey(), c));
                    }
                }
                dictionary.put(dictSize++, s + c);
                s = "";
            }
        }
        for (Map.Entry<Integer, String> entry : dictionary.entrySet()) {
            if (Objects.equals(entry.getValue(), s)) {
                encodedData.add(new Pair<>(entry.getKey(), null));
            }
        }
        return encodedData;
    }

    public String decode(ArrayList<Pair<Integer, Character>> encodedData) {
        StringBuilder decodedData = new StringBuilder();
        for (Pair<Integer, Character> pair : encodedData) {
            String entry = dictionary.get(pair.getKey()) + (pair.getValue() == null ? "" : pair.getValue());
            decodedData.append(entry);
            dictionary.put(dictSize++, entry);
        }
        return decodedData.toString();
    }

    public static class Pair<K, V> {
        private final K key;
        private final V value;

        public Pair(K key, V value) {
            this.key = key;
            this.value = value;
        }

        public K getKey() {
            return key;
        }

        public V getValue() {
            return value;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Введите строку для кодирования:");
        String data = reader.readLine();

        LZ78 lz78 = new LZ78();
        ArrayList<Pair<Integer, Character>> encodedData = lz78.encode(data);
        System.out.println("Закодированные данные: " + encodedData);

        String decodedData = lz78.decode(encodedData);
        System.out.println("Декодированные данные: " + decodedData);
    }
}
