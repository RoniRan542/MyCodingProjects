#include <stdio.h>  /* print */
#include <stdlib.h> /* NULL */
#define TEMPLATE_MAX(T)                 \
    T max_func##T(const T a, const T b) \
    {                                   \
        return a > b ? a : b;           \
    }

TEMPLATE_MAX(int)
TEMPLATE_MAX(double)

/*********************** TYPEDEFS *****************************/
typedef struct v_table_ptransport v_table_p;
typedef struct v_table_minibus v_table_m;
typedef struct v_table_taxi v_table_t;
typedef struct v_table_special_taxi v_table_s;

/*********************** STATIC/GLOBALS *****************************/

v_table_p v_table_ptrans;
v_table_m v_table_minibus;
v_table_t v_table_taxi;
v_table_s v_table_special_taxi;
static int g_s_count = 0;

/*********************** V-TABLES *****************************/
typedef struct PublicTransport
{
    v_table_p *v_ptr;
    int m_license_plate;
} p_transport_t;

typedef struct Minibus
{
    p_transport_t p_inherited;
    v_table_m *v_ptr;
    int m_numSeats;
} minibus_t;

typedef struct Taxi
{
    p_transport_t p_inherited;
    v_table_t *v_ptr;
} taxi_t;

typedef struct Special_Taxi
{
    taxi_t t_inherited;
    v_table_s *v_ptr;
} special_taxi_t;

struct v_table_ptransport
{
    void (*Dtor)(p_transport_t *this);
    void (*Display)(p_transport_t *this);
};

struct v_table_minibus
{
    void (*Dtor)(minibus_t *this);
    void (*Display)(minibus_t *this);
    void (*Wash)(minibus_t *this, int minutes);
};

struct v_table_taxi
{
    void (*Dtor)(taxi_t *this);
    void (*Display)(taxi_t *this);
};

struct v_table_special_taxi
{
    void (*Dtor)(special_taxi_t *this);
    void (*Display)(special_taxi_t *this);
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

/*********************** GLOBAL FUNCS *****************************/

static int GetID(p_transport_t *this)
{
    return this->m_license_plate;
}

static void PrintCount()
{
    printf("g_s_count: %d\n", g_s_count);
}

static void printInfoP(p_transport_t *p)
{
    p->v_ptr->Display(p);
}

void printInfoM(minibus_t *m)
{
    m->v_ptr->Wash(m, 3);
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
    printf("print_info_pm(int i)\n");
    ret.v_ptr->Display(&ret);
    PtransCopy(&p_ret, &ret.p_inherited);
    DtorMinibus(&ret);

    return p_ret;
}

void TaxiDisplay(taxi_t t)
{
    t.v_ptr->Display(&t);
}

/*********************** PUBLIC TRANSPORT *****************************/
void InitVtablePtrans(p_transport_t *this)
{
    this->v_ptr->Display = &DisplayPtrans;
    this->v_ptr->Dtor = &DtorPtrans;
}

void CtorPtrans(p_transport_t *this)
{
    this->v_ptr = &v_table_ptrans;
    InitVtablePtrans(this);
    this->m_license_plate = ++g_s_count;

    printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
}

void DtorPtrans(p_transport_t *this)
{
    this->v_ptr = NULL;
    --g_s_count;
    printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
}

void PtransAssignment(p_transport_t *p1, p_transport_t *p2)
{
    p2->m_license_plate = p1->m_license_plate;
    p2->v_ptr = p1->v_ptr;
}

void PtransCopy(p_transport_t *this, p_transport_t *p_other)
{
    (void)p_other;
    this->v_ptr = &v_table_ptrans;
    this->m_license_plate = ++g_s_count;
    printf("PublicTransport::copy()%d\n", this->m_license_plate);
}

void DisplayPtrans(p_transport_t *this)
{
    printf("PublicTransport::display()%d\n", this->m_license_plate);
}

/***********************  MINIBUS  ***********************/

void InitVtableMinibus(minibus_t *this)
{
    this->v_ptr->Display = &DisplayMinibus;
    this->v_ptr->Dtor = &DtorMinibus;
    this->v_ptr->Wash = &Wash;
}

void CtorMinibus(minibus_t *this)
{
    CtorPtrans(&(this->p_inherited));
    this->v_ptr = &v_table_minibus;
    InitVtableMinibus(this);
    this->m_numSeats = 20;

    printf("Minibus::Ctor()\n");
}

void DtorMinibus(minibus_t *this)
{
    this->v_ptr = NULL;
    printf("Minibus::Dtor()\n");
    DtorPtrans(&(this->p_inherited));
}

void MinibusCopy(minibus_t *this, minibus_t *m_other)
{
    PtransCopy(&this->p_inherited, &m_other->p_inherited);
    this->m_numSeats = m_other->m_numSeats;
    this->v_ptr = m_other->v_ptr;

    printf("Minibus::CCtor()\n");
}

void DisplayMinibus(minibus_t *this)
{
    printf("Minibus::display() ID: %d\n", GetID(&(this->p_inherited)));
    printf("num seats: %d\n", this->m_numSeats);
}

void Wash(minibus_t *this, int minutes)
{
    printf("Minibus::wash(%d) ID: %d\n", minutes, GetID(&(this->p_inherited)));
}

/***********************  TAXI  ***********************/

void InitVtableTaxi(taxi_t *this)
{
    this->v_ptr->Display = &DisplayTaxi;
    this->v_ptr->Dtor = &DtorTaxi;
}

void CtorTaxi(taxi_t *this)
{
    CtorPtrans(&(this->p_inherited));
    this->v_ptr = &v_table_taxi;
    InitVtableTaxi(this);

    printf("Taxi::Ctor()\n");
}

void DtorTaxi(taxi_t *this)
{
    this->v_ptr = NULL;
    printf("Taxi::Dtor()\n");
    DtorPtrans(&(this->p_inherited));
}

void TaxiCopy(taxi_t *this, taxi_t *t_other)
{
    printf("Taxi::CCtor()\n");
    PtransCopy(&this->p_inherited, &t_other->p_inherited);
    this->v_ptr = t_other->v_ptr;
}

void DisplayTaxi(taxi_t *this)
{
    printf("Taxi::display() ID: %d\n", GetID(&this->p_inherited));
}

/***********************  SPECIAL TAXI  ***********************/

void InitVtableSpecialTaxi(special_taxi_t *this)
{
    this->v_ptr->Display = &DisplaySpecialTaxi;
    this->v_ptr->Dtor = &DtorSpecialTaxi;
}

void CtorSpecialTaxi(special_taxi_t *this)
{
    CtorTaxi(&(this->t_inherited));
    this->v_ptr = &v_table_special_taxi;
    InitVtableSpecialTaxi(this);

    printf("SpecialTaxi::Ctor()\n");
}

void DtorSpecialTaxi(special_taxi_t *this)
{
    this->v_ptr = NULL;
    DtorTaxi(&(this->t_inherited));
    printf("SpecialTaxi::Dtor()\n");
}

void SpecialTaxiCopy(special_taxi_t *this, special_taxi_t *s_other)
{
    TaxiCopy(&this->t_inherited, &s_other->t_inherited);
    printf("SpecialTaxi::CCtor()\n");
    this->v_ptr = s_other->v_ptr;
}

void DisplaySpecialTaxi(special_taxi_t *this)
{
    printf("SpecialTaxi::display() ID: %d\n", GetID(&this->t_inherited.p_inherited));
}

void FreeResourcesTaxi(taxi_t **arr, size_t len)
{
    size_t i = 0;
    for (i = 0; i < len; i++)
    {
        DtorTaxi(arr[i]);
        free(arr[i]);
    }
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
    p.v_ptr->Display(&p);
    /* dynamic alocations*/

    array[0] = malloc(sizeof(minibus_t));
    if (NULL == array[0])
    {
        exit(1);
    }
    CtorMinibus((minibus_t *)array[0]);

    array[1] = malloc(sizeof(taxi_t));
    if (NULL == array[1])
    {
        exit(1);
    }
    CtorTaxi((taxi_t *)array[1]);

    array[2] = malloc(sizeof(minibus_t));
    if (NULL == array[2])
    {
        exit(1);
    }
    CtorMinibus((minibus_t *)array[2]);

    ((minibus_t *)array[0])->v_ptr->Display((minibus_t *)array[0]);
    ((taxi_t *)array[1])->v_ptr->Display((taxi_t *)array[1]);
    ((minibus_t *)array[2])->v_ptr->Display((minibus_t *)array[2]);

    /* static allocations*/
    CtorMinibus(&temp1);
    PtransCopy(&array2[0], &temp1.p_inherited);
    DtorMinibus(&temp1);
    CtorTaxi(&temp2);
    PtransCopy(&array2[1], &temp2.p_inherited);
    DtorTaxi(&temp2);
    CtorPtrans(&array2[2]);
    array2[0].v_ptr->Display(&array2[0]);
    array2[1].v_ptr->Display(&array2[1]);
    array2[2].v_ptr->Display(&array2[2]);
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
        if (NULL == array4[i])
        {
            exit(1);
        }
        CtorTaxi(array4[i]);
    }

    FreeResourcesTaxi(array4, 4);

    printf("%d\n", max_funcint(1, 2));
    printf("%d\n", max_funcint(1, 2.0f));

    CtorSpecialTaxi(&st);
    TaxiCopy(&temp2, &st.t_inherited);
    TaxiDisplay(temp2);
    DtorTaxi(&temp2);

    /* Destractores */
    /*  DtorMinibus((minibus_t *)&array2[0]);
     DtorTaxi((taxi_t *)&array2[1]);
     DtorPtrans(&array2[2]);
     DtorMinibus((minibus_t *)array[0]);
     DtorTaxi((taxi_t *)array[1]);
     DtorMinibus((minibus_t *)array[2]);
     for (i = 0; i < 3; ++i)
     {
         free(array[i]);
         array[i] = NULL;
     }

     DtorMinibus(&m);
     DtorPtrans(&p);
  */
    return 0;
}