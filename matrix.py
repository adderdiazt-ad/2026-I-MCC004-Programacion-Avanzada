import _matrix
def matrix(rows, cols, dtype=float):
    if dtype == float:
        return _matrix.MatrixDouble(rows, cols)
    elif dtype == int:
        return _matrix.MatrixInt(rows, cols)
    else:
        raise TypeError(f"Tipo de dato '{dtype}' no soportado. Usa float o int.")