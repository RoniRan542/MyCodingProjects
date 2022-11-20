/*********************************
Author: Ran
Reviewer: Chen
Date: 07.09.22
**********************************/
#include <stdio.h>  /* print */
#include <stdlib.h> /* NULL */

/*********************** TYPEDEFS *****************************/
typedef struct v_table_ptransport v_table_p;
typedef struct v_table_minibus v_table_m;
typedef struct v_table_taxi v_table_t;
typedef struct v_table_special_taxi v_table_s;
typedef struct v_table_convoy v_table_c;

/*********************** STATIC/GLOBALS *****************************/

static int g_s_count = 0;

/*********************** V-TABLES *****************************/
typedef struct PublicTransport
{
    void *v_ptr;
    int m_license_plate;
} p_transport_t;

typedef struct Minibus
{
    p_transport_t p_inherited;
    int m_numSeats;
} minibus_t;

typedef struct Taxi
{
    p_transport_t p_inherited;
} taxi_t;

typedef struct Special_Taxi
{
    taxi_t t_inherited;
} special_taxi_t;

typedef struct PublicConvoy
{
    p_transport_t p_inherited;
    p_transport_t *pt1;
    p_transport_t *pt2;
    minibus_t m;
    taxi_t t;
} public_convoy_t;

struct v_table_ptransport
{
    void (*Display)(p_transport_t *this);
    void (*Dtor)(p_transport_t *this);
};

struct v_table_minibus
{
    void (*Display)(minibus_t *this);
    void (*Dtor)(minibus_t *this);
    void (*Wash)(minibus_t *this, int minutes);
};

struct v_table_taxi
{
    void (*Display)(taxi_t *this);
    void (*Dtor)(taxi_t *this);
};

struct v_table_special_taxi
{
    void (*Display)(special_taxi_t *this);
    void (*Dtor)(special_taxi_t *this);
};

struct v_table_convoy
{
    void (*Display)(public_convoy_t *this);
    void (*Dtor)(public_convoy_t *this);
};

/*********************** FUNC DECLERATION ************************/

void DisplayPtrans(p_transport_t *this);
void InitVtablePtrans(p_transport_t *this);
void DtorPtrans(p_transport_t *this);
void CtorPtrans(p_transport_t *this);
void InitVtableMinibus(minibus_t *this);
void CtorMinibus(minibus_t *this);
void DtorMinibus(minibus_t *this);
void DisplayMinibus(minibus_t *this);
void Wash(minibus_t *this, int minutes);
void InitVtableTaxi(taxi_t *this);
void CtorTaxi(taxi_t *this);
void DtorTaxi(taxi_t *this);
void DisplayTaxi(taxi_t *this);
void InitVtableSpecialTaxi(special_taxi_t *this);
void CtorSpecialTaxi(special_taxi_t *this);
void DtorSpecialTaxi(special_taxi_t *this);
void SpecialTaxiCopy(special_taxi_t *this, special_taxi_t *s_other);
void DisplaySpecialTaxi(special_taxi_t *this);
void PtransCopy(p_transport_t *this, p_transport_t *p_other);
void DisplayPublicConvoy(public_convoy_t *this);
void DtorPublicConvoy(public_convoy_t *this);

v_table_p v_table_ptrans = {&DisplayPtrans, &DtorPtrans};
v_table_m v_table_minibus = {&DisplayMinibus, &DtorMinibus, &Wash};
v_table_t v_table_taxi = {&DisplayTaxi, &DtorTaxi};
v_table_s v_table_special_taxi = {&DisplaySpecialTaxi, &DtorSpecialTaxi};
v_table_c v_table_convoy = {&DisplayPublicConvoy, &DtorPublicConvoy};

/*********************** GLOBAL FUNCS *****************************/

static int GetID(p_transport_t *this)
{
    return this->m_license_plate;
}

static void PrintCount()
{
    printf("s_count: %d\n", g_s_count);
}

static void printInfoP(p_transport_t *p)
{
    ((v_table_p *)(p->v_ptr))->Display(p);
}

void printInfoM(minibus_t *m)
{
    ((v_table_m *)(m->p_inherited.v_ptr))->Wash(m, 3);
}

void printInfoCount()
{
    PrintCount();
}

p_transport_t printInfoPM(int i)
{
    minibus_t ret;
    p_transport_t p_ret;
    CtorMinibus(&ret);
    (void)i;
    printf("print_info(int i)\n");
    DisplayMinibus(&ret); /*static binding*/
    PtransCopy(&p_ret, &ret.p_inherited);
    DtorMinibus(&ret);

    return p_ret;
}

void TaxiDisplay(taxi_t t)
{
    DisplayTaxi(&t); /*static binding*/
}

/*********************** PUBLIC TRANSPORT *****************************/
void CtorPtrans(p_transport_t *this)
{
    this->v_ptr = &v_table_ptrans;
    this->m_license_plate = ++g_s_count;

    printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
}

void DtorPtrans(p_transport_t *this)
{
    this->v_ptr = NULL;
    --g_s_count;
    printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
}

void PtransCopy(p_transport_t *this, p_transport_t *p_other)
{
    (void)p_other;
    this->v_ptr = &v_table_ptrans;
    this->m_license_plate = ++g_s_count;
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void DisplayPtrans(p_transport_t *this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

/***********************  MINIBUS  ***********************/
void CtorMinibus(minibus_t *this)
{
    CtorPtrans(&(this->p_inherited));
    this->p_inherited.v_ptr = &v_table_minibus;
    this->m_numSeats = 20;

    printf("Minibus::Ctor()\n");
}

void DtorMinibus(minibus_t *this)
{
    printf("Minibus::Dtor()\n");
    DtorPtrans(&(this->p_inherited));
}

void MinibusCopy(minibus_t *this, minibus_t *m_other)
{
    PtransCopy(&this->p_inherited, &m_other->p_inherited);
    this->m_numSeats = m_other->m_numSeats;
    this->p_inherited.v_ptr = m_other->p_inherited.v_ptr;

    printf("Minibus::CCtor()\n");
}

void DisplayMinibus(minibus_t *this)
{
    printf("Minibus::display() ID:%d ", GetID(&(this->p_inherited)));
    printf("num seats:%d\n", this->m_numSeats);
}

void Wash(minibus_t *this, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, GetID(&(this->p_inherited)));
}

/***********************  TAXI  ***********************/
void CtorTaxi(taxi_t *this)
{
    CtorPtrans(&(this->p_inherited));
    this->p_inherited.v_ptr = &v_table_taxi;

    printf("Taxi::Ctor()\n");
}

void DtorTaxi(taxi_t *this)
{
    printf("Taxi::Dtor()\n");
    DtorPtrans(&(this->p_inherited));
}

void TaxiCopy(taxi_t *this, taxi_t *t_other)
{
    PtransCopy(&this->p_inherited, &t_other->p_inherited);
    this->p_inherited.v_ptr = t_other->p_inherited.v_ptr;
    printf("Taxi::CCtor()\n");
}

void DisplayTaxi(taxi_t *this)
{
    printf("Taxi::display() ID:%d\n", GetID(&this->p_inherited));
}

/***********************  SPECIAL TAXI  ***********************/
void CtorSpecialTaxi(special_taxi_t *this)
{
    CtorTaxi(&(this->t_inherited));
    this->t_inherited.p_inherited.v_ptr = &v_table_special_taxi;

    printf("SpecialTaxi::Ctor()\n");
}

void DtorSpecialTaxi(special_taxi_t *this)
{
    printf("SpecialTaxi::Dtor()\n");
    DtorTaxi(&(this->t_inherited));
}

/***********************  SPECIAL PUBLIC-CONVOY  ***********************/
void CtorPublicConvoy(public_convoy_t *this)
{
    CtorPtrans(&(this->p_inherited));
    this->p_inherited.v_ptr = &v_table_convoy;

    this->pt1 = (p_transport_t *)malloc(sizeof(minibus_t));
    CtorMinibus((minibus_t *)this->pt1);
    this->pt2 = (p_transport_t *)malloc(sizeof(taxi_t));
    CtorTaxi((taxi_t *)this->pt2);

    CtorMinibus(&this->m);
    CtorTaxi(&this->t);
}

void CopyPublicConvoy(public_convoy_t *this, public_convoy_t *other)
{
    PtransCopy(&this->p_inherited, &other->p_inherited);
    this->p_inherited.v_ptr = other->p_inherited.v_ptr;
    this->pt1 = malloc(sizeof(minibus_t));
    this->pt2 = malloc(sizeof(taxi_t));
    MinibusCopy((minibus_t *)(this->pt1), (minibus_t *)(other->pt1));
    TaxiCopy((taxi_t *)(this->pt2), (taxi_t *)(other->pt2));
    MinibusCopy(&this->m, &other->m);
    TaxiCopy(&this->t, &other->t);
}

void DisplayPublicConvoy(public_convoy_t *this)
{
    ((v_table_m *)(((minibus_t *)(this->pt1))->p_inherited.v_ptr))->Display((minibus_t *)(this->pt1));
    ((v_table_t *)(((taxi_t *)(this->pt2))->p_inherited.v_ptr))->Display((taxi_t *)(this->pt2));
    DisplayMinibus(&this->m);
    DisplayTaxi(&this->t);
}

void DtorPublicConvoy(public_convoy_t *this)
{
    ((v_table_m *)(((minibus_t *)(this->pt1))->p_inherited.v_ptr))->Dtor((minibus_t *)this->pt1);
    free(this->pt1);
    ((v_table_t *)(((taxi_t *)(this->pt2))->p_inherited.v_ptr))->Dtor((taxi_t *)(this->pt2));
    free(this->pt2);
    DtorTaxi(&this->t);
    DtorMinibus(&this->m);
    DtorPtrans(&this->p_inherited);
}

void SpecialTaxiCopy(special_taxi_t *this, special_taxi_t *s_other)
{
    TaxiCopy(&this->t_inherited, &s_other->t_inherited);
    printf("SpecialTaxi::CCtor()\n");
    this->t_inherited.p_inherited.v_ptr = s_other->t_inherited.p_inherited.v_ptr;
}

void DisplaySpecialTaxi(special_taxi_t *this)
{
    printf("SpecialTaxi::display() ID:%d\n", GetID(&this->t_inherited.p_inherited));
}

void FreeResourcesTaxi(taxi_t **arr, size_t len)
{
    size_t i = len;
    for (; i != 0; --i)
    {
        DtorTaxi(arr[i - 1]);
        free(arr[i - 1]);
    }
}

int Max_int(const int a, const int b)
{
    return a > b ? a : b;
}

double Max_double(const double a, const double b)
{
    return a > b ? a : b;
}

int main()
{
    minibus_t m;
    minibus_t m2;
    int i = 0;
    p_transport_t p;
    p_transport_t *array[3];
    p_transport_t array2[3];
    minibus_t array3[4];
    taxi_t *array4[4];
    minibus_t temp1;
    taxi_t temp2;
    special_taxi_t st;

    CtorMinibus(&m);
    printInfoM(&m);
    p = printInfoPM(3);
    DisplayPtrans(&p);
    DtorPtrans(&p);

    /* dynamic alocations*/

    array[0] = malloc(sizeof(minibus_t));
    CtorMinibus((minibus_t *)array[0]);

    array[1] = malloc(sizeof(taxi_t));
    CtorTaxi((taxi_t *)array[1]);

    array[2] = malloc(sizeof(minibus_t));
    CtorMinibus((minibus_t *)array[2]);

    ((v_table_m *)(((minibus_t *)array[0])->p_inherited.v_ptr))->Display((minibus_t *)array[0]);
    ((v_table_t *)(((taxi_t *)array[1])->p_inherited.v_ptr))->Display((taxi_t *)array[1]);
    ((v_table_m *)(((minibus_t *)array[2])->p_inherited.v_ptr))->Display((minibus_t *)array[2]);

    DtorMinibus((minibus_t *)array[0]);
    free(array[0]);

    DtorTaxi((taxi_t *)array[1]);
    free(array[1]);

    DtorMinibus((minibus_t *)array[2]);
    free(array[2]);

    /* static allocations*/
    CtorMinibus(&temp1);
    PtransCopy(&array2[0], &temp1.p_inherited);
    DtorMinibus(&temp1);
    CtorTaxi(&temp2);
    PtransCopy(&array2[1], &temp2.p_inherited);
    DtorTaxi(&temp2);
    CtorPtrans(&array2[2]);
    ((v_table_p *)array2[0].v_ptr)->Display(&array2[0]);
    ((v_table_t *)array2[1].v_ptr)->Display((taxi_t *)&array2[1]);
    ((v_table_p *)array2[2].v_ptr)->Display(&array2[2]);
    printInfoP(&array2[0]);
    PrintCount();
    CtorMinibus(&m2);
    PrintCount();

    for (i = 0; i < 4; i++)
    {
        CtorMinibus(&array3[i]);
    }

    for (i = 0; i < 4; i++)
    {
        array4[i] = malloc(sizeof(taxi_t));
        CtorTaxi(array4[i]);
    }

    FreeResourcesTaxi(array4, 4);

    printf("%d\n", Max_int(1, 2));
    printf("%d\n", Max_int(1, 2.0f));

    CtorSpecialTaxi(&st);
    TaxiCopy(&temp2, &st.t_inherited);
    DisplayTaxi(&temp2);
    DtorTaxi(&temp2);

    {
        public_convoy_t *ts1 = malloc(sizeof(public_convoy_t));
        public_convoy_t *ts2 = malloc(sizeof(public_convoy_t));
        CtorPublicConvoy(ts1);
        CopyPublicConvoy(ts2, ts1);

        ((v_table_c *)ts1->p_inherited.v_ptr)->Display(ts1);
        ((v_table_c *)ts2->p_inherited.v_ptr)->Display(ts2);

        DtorPublicConvoy(ts1);
        free(ts1);
        ((v_table_c *)ts2->p_inherited.v_ptr)->Display(ts2);
        DtorPublicConvoy(ts2);
        free(ts2);
    }

    /* Destractors */
    DtorSpecialTaxi(&st);
    for (i = 4; i > 0; --i)
    {
        DtorMinibus(&array3[i - 1]);
    }
    DtorMinibus(&m2);
    DtorPtrans(&array2[2]);
    DtorPtrans(&array2[1]);
    DtorPtrans(&array2[0]);
    DtorMinibus(&m);

    return 0;
}