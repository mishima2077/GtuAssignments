import java.util.Map;

public class encryptor {
	private Map<Character, Map<Character, Character>> map;
	private String key;
	private String keystream = "";
	private String plain_text;
	private String cipher_text = "";
	
	public encryptor(Map<Character, Map<Character, Character>> _map, String _key, String text) {
		map = _map;

		//Preprocessing the given data and seting up our initial values
		preprocessor p = new preprocessor(_key);
		p.preprocess();
		key = p.get_preprocessed_string();

		p = new preprocessor(text);
		p.preprocess();
		plain_text = p.get_preprocessed_string();
	}
	
	public void encrypt() {
		// do not edit this method
		generate_keystream();
		generate_cipher_text();
	}
	
	private void generate_keystream() {
		int keyLen = key.length();
		StringBuilder sb = new StringBuilder();

		//Generate the keystream by repeating the key
		for(int i = 0; i < plain_text.length(); ++i){
			//Circularly loop the key
			sb.append(key.charAt(i % keyLen));
		}

		keystream = sb.toString();
	}
	
	private void generate_cipher_text() {
		//Initialize the string builder
		StringBuilder sb = new StringBuilder();
		
		for(int i = 0; i < plain_text.length(); ++i){
			//Find the correct encrypted character from the map and append it to the string builder
			sb.append(map.get(plain_text.charAt(i)).get(keystream.charAt(i)));
		}
		
		//Set the cipher text
		cipher_text = sb.toString();
	}

	public String get_keystream() {
		return keystream;
	}
	
	public String get_cipher_text() {
		return cipher_text;
	}
}
