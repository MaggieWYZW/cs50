from enum import Enum

class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """
    Calculate edit distance from a to b
    Return a matrix
    """

    height, width = len(a)+1, len(b)+1
    edit_distance = [[( ) for _ in range(width)] for _ in range(height)]

    # fill in the base of the matrix
    edit_distance[0][0] = (0, None)
    for i in range(1, width):
        # first row of the matrix
        edit_distance[0][i] = (i, Operation.INSERTED)
    for i in range(1, height):
        # first column of the matrix
        edit_distance[i][0] = (i, Operation.DELETED)

    # fill in the rest of the matrix
    for i in range(1, height):
        for j in range(1, width):
            if a[i-1] == b[j-1]:
                # no operations needed
                edit_distance[i][j] = (edit_distance[i-1][j-1][0], None)
            else:
                # operations needed with costs
                edit_distance[i][j] = (edit_distance[i-1][j-1][0] + 1, Operation.SUBSTITUTED)
                tmp = (edit_distance[i-1][j][0] + 1, Operation.DELETED)
                if tmp[0] < edit_distance[i][j][0]:
                    edit_distance[i][j] = tmp
                tmp = (edit_distance[i][j-1][0] + 1, Operation.INSERTED)
                if tmp[0] < edit_distance[i][j][0]:
                    edit_distance[i][j] = tmp

    return edit_distance
