def lines(a, b):
    """Return lines in both a and b"""
    common_lines = set()
    lines_a = a.split()
    lines_b = b.split()
    for line in lines_a:
        if line in lines_b:
            common_lines.add(line)

    return list(common_lines)


def sentences(a, b):
    """Return sentences in both a and b"""
    from nltk.tokenize import sent_tokenize
    common_sentences = set()
    sentences_a = sent_tokenize(a)
    sentences_b = sent_tokenize(b)

    for sentence in sentences_a:
        if sentence in sentences_b:
            common_sentences.add(sentence)

    return list(common_sentences)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    common_strs = set()

    substrs_a = [a[i:i+n] for i in range(len(a)-n)]
    substrs_b = [b[i:i+n] for i in range(len(b)-n)]

    for substr in substrs_a:
        if substr in substrs_b:
            common_strs.add(substr)

    return list(common_strs)
