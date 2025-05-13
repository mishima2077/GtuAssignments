public class preprocessor {
	private String initial_string;
	private String preprocessed_string;
		
	public preprocessor(String str) {
		initial_string = str;
	}

	public void preprocess() {
		// do not edit this method
		capitalize();
		clean();
	}
	
	private void capitalize() {
		preprocessed_string = initial_string.toUpperCase();
	}

	private void clean() {
		StringBuilder temp = new StringBuilder();
		for (char c : preprocessed_string.toCharArray()) { //Iterate through the string and add every char which is a letter
			if (c >= 'A' && c <= 'Z') temp.append(c);
		}
		
		preprocessed_string = temp.toString();
	}
	
	public String get_preprocessed_string() {
		return preprocessed_string;
	}
}