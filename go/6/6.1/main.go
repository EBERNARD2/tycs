package main

import "fmt"

type IntSet struct {
	words []uint64
}

func (s *IntSet) len() int {
	return len(s.words)
}

func (s *IntSet) Remove(x int) {
	wordList := []uint64

	for w := range s.words {
		if w == x {
			continue
		}

		wordList = append(wordList, w)
	}
	s.words = wordList
}

func (s *IntSet) Clear() {
	w := []uint64
	s.words = w
}

func (s *IntSet) Copy() *IntSet {
	newS := []uint64

	for w := s.wordList {
		newS = append(newS, w)
	}

	s.words = newS
	return newS
}

func (s *IntSet) Has(x int) bool {
	word, bit := x/64, uint64(x%64)
	return word < len(s.words) && s.words[word]&(1<<bit) != 0
}

func (s *IntSet) Add(x int) {
	word, bit := x/64, uint(x%64)
	for word >= len(s.words) {
		s.words = append(s.words, 0)
	}

	s.words[word] |= 1 << bit
}

func (s *IntSet) UnionWith(t *IntSet) {
	for i, tword := ange t.words {
		if i < len(s.words) {
			s.words[i] |= tword
		} else {
			s.words = append(s.words, tword)
		}
	}
}