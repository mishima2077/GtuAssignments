import java.util.HashMap;
import java.util.Map;
import java.util.LinkedHashSet;
import java.util.Set;
import java.util.Iterator;

public class alphabet {
	private Set<Character> english_alphabet = new LinkedHashSet<Character>();
	private Map<Character, Map<Character, Character>> map = new HashMap<Character,  Map<Character, Character>>();
	
	public alphabet() {
		// do not edit this method
		fill_english_alphabet();
		fill_map();
	}
	
	private void fill_english_alphabet() {
		// do not edit this method
		for(char c : "ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray()) {
		    english_alphabet.add(c);
		}
	}
	
	private void fill_map() {
		// You must use the "english_alphabet" variable in this method, to fill the "map" variable.
		// You can define 1 or 2 iterators to iterate through the set items.

		//Initialize the iterators and the temporary map
		Iterator<Character> i = english_alphabet.iterator();
		char iVal;
		Iterator<Character> j = english_alphabet.iterator();
		char jVal;
		Map<Character,Character> temp;
		
		while(i.hasNext()){
			iVal = i.next();
			temp = new HashMap<Character,Character>(); //Reset the temporary map
			
			while(j.hasNext()){ //This part circularly loops the iterator i , and normally loops the iterator j
								//Because of this, difference between them always stays same within this loop
				jVal = j.next();
				temp.put(jVal, iVal);

				if(!i.hasNext()) i = english_alphabet.iterator(); //If i has come to end, return it to the begining
				iVal = i.next();
			}
			j = english_alphabet.iterator(); //Reset the iterator j

			map.put(iVal, temp); //Put the values to the main map
		}
	}

	public void print_map() {
		// do not edit this method
		System.out.println("*** Viegenere Cipher ***\n\n");
		System.out.println("    " + english_alphabet);
		System.out.print("    ------------------------------------------------------------------------------");
		for(Character k: map.keySet()) {
			System.out.print("\n" + k + " | ");
			System.out.print(map.get(k).values());
		}
		System.out.println("\n");
		
	}

	public Map get_map() {
		return map;
	}
}