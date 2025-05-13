import java.util.Map;
import java.util.Iterator;

public class decryptor {
	private Map<Character, Map<Character, Character>> map;
	private String key;
	private String keystream = "";
	private String plain_text = "";
	private String cipher_text;
	
	public decryptor(Map<Character, Map<Character, Character>> _map, String _key, String text) {
		map = _map;

		//Preprocessing the given data and seting up our initial values
		preprocessor p = new preprocessor(_key);
		p.preprocess();
		key = p.get_preprocessed_string();

		p = new preprocessor(text);
		p.preprocess();
		cipher_text = p.get_preprocessed_string();
	}

	public void decrypt() {
		// do not edit this method
		generate_keystream();
		generate_plain_text();
	}
	
	private void generate_keystream() {
		int keyLen = key.length();
		StringBuilder sb = new StringBuilder();
		
		//Generate the keystream by repeating the key
		for(int i = 0; i < cipher_text.length(); ++i){
			//Circularly loop the key
			sb.append(key.charAt(i % keyLen));
		}

		keystream = sb.toString();
	}
	
	private void generate_plain_text() {
		// You must use map.get(x).keySet() with an iterator in this method

		//Initialize the string builder
		StringBuilder sb = new StringBuilder();

		Iterator<Character> it;
		char itVal;

		for(int i = 0; i < cipher_text.length(); ++i){
			//Initialize the iterator
			it = map.get(keystream.charAt(i)).keySet().iterator();
			
			//Loop through the iterator
			while(it.hasNext()){
				itVal = it.next();
				//Find the correct encrypted character from the map and append it to the string builder
				if(map.get(keystream.charAt(i)).get(itVal) == cipher_text.charAt(i)){
					sb.append(itVal);
					break;
				}
			}
		}

		plain_text = sb.toString();
	}

	public String get_keystream() {
		return keystream;
	}
	
	public String get_plain_text() {
		return plain_text;
	}
}
