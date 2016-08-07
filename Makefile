deckoffset: deckoffset.c
	$(CC) -o deckoffset deckoffset.c -lm

clean:
	rm -f deckoffset
