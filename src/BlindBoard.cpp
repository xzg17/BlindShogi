#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "BlindBoard.hpp"

typedef struct {
    
    PyObject_HEAD
    /* Type-specific fields go here. */
        Board *board;
} Py_Board;

static int *board_init(Py_Board *self);
static PyObject *dummy(PyObject *args){
    return PyBuild_Value("i", 0);
};
static PyMethodDef Py_Board_methods[] = {
    //{"test", (PyCFunction)test_func, METH_VARARGS, "(ToT)"},
    {"dummy", (PyCFunction)dummy, METH_NOARGS, "(ToT)"},
    {NULL} /* Sentinel */
};


static PyTypeObject BoardType = {
    PyVarObject_HEAD_INIT(NULL, 0) "custom.Custom", /* tp_name */
    sizeof(Py_Board),                           /* tp_basicsize */
    0,                                              /* tp_itemsize */
    /* methods */
    0, /* tp_dealloc */
    0,                        /* tp_print */
    0,                        /* tp_getattr */
    0,                        /* tp_setattr */
    0,                        /* tp_reserved */
    0,                        /* tp_repr */
    0,                        /* tp_as_number */
    0,                        /* tp_as_sequence */
    0,                        /* tp_as_mapping */
    0,                        /* tp_hash */
    0,                        /* tp_call */
    0,     /* tp_str */
    0,                        /* tp_getattro */
    0,                        /* tp_setattro */
    0,                        /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,       /* tp_flags */
    PyDoc_STR("Custom objects"),/* tp_doc */
    0,                        /* tp_traverse */
    0,                        /* tp_clear */
    0,                        /* tp_richcompare */
    0,                        /* tp_weaklistoffset */
    0,                        /* tp_iter */
    0,                        /* tp_iternext */
    Py_Board_methods,    /* tp_methods */
    0,                        /* tp_members */
    0,                        /* tp_getset */
    0,                        /* tp_base */
    0,                        /* tp_dict */
    0,                        /* tp_descr_get */
    0,                        /* tp_descr_set */
    0,                        /* tp_dictoffset */
    (initproc)board_init,     /* tp_init */
    0,                        /* tp_alloc */
    PyType_GenericNew,        /* tp_new */
};

static int *board_init(Py_Board *self){
    self->board = new Board();
    return 0;
};

static PyModuleDef blind_board = {
    PyModuleDef_HEAD_INIT,
    "BlindBoard",
    "Example module that creates an extension type.",
    -1,
    NULL
};

PyMODINIT_FUNC
PyInit_BlindBoard(void){
    PyObject *m;
    
    m = PyModule_Create(&blind_board);
    if (m == NULL){
        return NULL;
    }
        
    if (PyType_Ready(&BoardType) < 0){
        return NULL;
    }

    Py_INCREF(&BoardType);
    PyModule_AddObject(m, "BlindBoard", (PyObject *) &BoardType);

    return m;
};
