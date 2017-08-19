import nltk
from nltk.tokenize import TweetTokenizer

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positive_set = set()
        file = open(positives, "r")
        
        for line in file:
            if line.startswith(';') == False:
                self.positive_set.add(line.rstrip("\n"))
        
        self.negative_set = set()
        file = open(negatives, "r")
        
        for line in file:
            if line.startswith(';') == False:
                self.negative_set.add(line.rstrip("\n"))
        # TODO

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        token = TweetTokenizer()
        split_text = token.tokenize(text)
        sum = 0
        
        for word in split_text:
            if word.lower() in self.positive_set:
                sum += 1
            elif word.lower() in self.negative_set:
                sum -= 1
            else:
                continue
        return sum
        # TODO
