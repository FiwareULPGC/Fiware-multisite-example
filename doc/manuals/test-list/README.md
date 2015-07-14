#List test

##code inside list

* Install the required tools. You need lcov 1.10 - the one that comes with CentOS 6.3 (lcov 1.9) is not valid.

        sudo rpm -Uhv http://downloads.sourceforge.net/ltp/lcov-1.10-1.noarch.rpm

* Prepare the environment for test harness. Basically, you have to install the accumulator-server.py script and in a path under your control, ~/bin is the recommended one. Alternatively, you can install them in a system directory such as /usr/bin but it could collide with an RPM installation, thus it is not recommended. In addition, you have to set several environment variables used by the harness script (see scripts/testEnv.sh file).

        mkdir ~/bin export PATH=~/bin:$PATH make install_scripts INSTALL_DIR=~ . scripts/testEnv.sh 



##code after list without code inside

* Install the required tools. You need lcov 1.10 - the one that comes with CentOS 6.3 (lcov 1.9) is not valid.

       
* Prepare the environment for test harness. Basically, you have to install the accumulator-server.py script and in a path under your control, ~/bin is the recommended one. Alternatively, you can install them in a system directory such as /usr/bin but it could collide with an RPM installation, thus it is not recommended. In addition, you have to set several environment variables used by the harness script (see scripts/testEnv.sh file). 
Orion Context Broker reference distribution is CentOS 6.x. This doesn't mean that the broker cannot be built in other distributions (actually, it can). This section also includes indications on how to build in other distributions, just in the case it may help people that don't use CentOS. However, note that the only "officially supported" procedure is the one for CentOS 6.x; the others are provided "as is" and can get obsolete from time to time.


```.json

{

    "contextResponses": [

        {

            "contextElement": {

                "attributes": [

                    {

                        "name": "attrName",

                        "values": [

                            {

                                "recvTime": "2014-02-14T13:43:33.306Z",

                                "attrValue": "21.28"

                            },

                            {

                                "recvTime": "2014-02-14T13:43:34.636Z",

                                "attrValue": "23.42"

                            },

                            {

                                "recvTime": "2014-02-14T13:43:35.424Z",

                                "attrValue": "22.12"

                            }

                        ]

                    }

                ],

                "id": "entityId",

                "isPattern": false

            },

            "statusCode": {

                "code": "200",

                "reasonPhrase": "OK"

            }

        }

    ]

}

```

##code after list withcode inside

* Install the required tools. You need lcov 1.10 - the one that comes with CentOS 6.3 (lcov 1.9) is not valid.

        sudo rpm -Uhv http://downloads.sourceforge.net/ltp/lcov-1.10-1.noarch.rpm

* Prepare the environment for test harness. Basically, you have to install the accumulator-server.py script and in a path under your control, ~/bin is the recommended one. Alternatively, you can install them in a system directory such as /usr/bin but it could collide with an RPM installation, thus it is not recommended. In addition, you have to set several environment variables used by the harness script (see scripts/testEnv.sh file).

        mkdir ~/bin export PATH=~/bin:$PATH make install_scripts INSTALL_DIR=~ . scripts/testEnv.sh 

* Install the required tools. You need lcov 1.10 - the one that comes with CentOS 6.3 (lcov 1.9) is not valid.

       
* Prepare the environment for test harness. Basically, you have to install the accumulator-server.py script and in a path under your control, ~/bin is the recommended one. Alternatively, you can install them in a system directory such as /usr/bin but it could collide with an RPM installation, thus it is not recommended. In addition, you have to set several environment variables used by the harness script (see scripts/testEnv.sh file). 
Orion Context Broker reference distribution is CentOS 6.x. This doesn't mean that the broker cannot be built in other distributions (actually, it can). This section also includes indications on how to build in other distributions, just in the case it may help people that don't use CentOS. However, note that the only "officially supported" procedure is the one for CentOS 6.x; the others are provided "as is" and can get obsolete from time to time.


```.json

{

    "contextResponses": [

        {

            "contextElement": {

                "attributes": [

                    {

                        "name": "attrName",

                        "values": [

                            {

                                "recvTime": "2014-02-14T13:43:33.306Z",

                                "attrValue": "21.28"

                            },

                            {

                                "recvTime": "2014-02-14T13:43:34.636Z",

                                "attrValue": "23.42"

                            },

                            {

                                "recvTime": "2014-02-14T13:43:35.424Z",

                                "attrValue": "22.12"

                            }

                        ]

                    }

                ],

                "id": "entityId",

                "isPattern": false

            },

            "statusCode": {

                "code": "200",

                "reasonPhrase": "OK"

            }

        }

    ]

}

```


##img test2
Esto es una imagen fuera de nigún bloque, necesita  una salto de línea intermedio

![texto alternativo2](http://fotos01.laprovincia.es/fotos/noticias/318x200/2012-08-17_IMG_2012-08-10_01.55.14__6466673.jpg)


##img test
Esto es una imagen dentro de un bloque pre no debe tener espacio de separación con el párrafo.
orem Ipsum es simplemente el texto de relleno de las imprentas y archivos de texto. Lorem Ipsum ha sido el texto de relleno estándar de las industrias desde el año 1500, cuando un impresor (N. del T. persona que se dedica a la imprenta) desconocido usó una galería de textos y los mezcló de tal manera que logró hacer un libro de textos especimen. No sólo sobrevivió 500 años, sino que tambien ingresó como texto de relleno en documentos electrónicos, quedando esencialmente igual al original. Fue popularizado en los 60s con la creación de las hojas "Letraset", las cuales contenian pasajes de Lorem Ipsum, y más recientemente con software de autoedición, como por ejemplo Aldus PageMaker, el cual incluye versiones de Lorem Ipsum.
<pre>
	![texto alternativo](http://www.holidayworldmaspalomas.com/wp-content/uploads/2014/09/Aniversario-Holiday-World-Maspalomas-2014-IMG-20140825-WA0039.jpg)
</pre>


##img test con código img izquierda y código a la derecha

asdfadfasdf
asdfasd

![texto alternativo2](http://hivdb.stanford.edu/images/schema.gif)

```.json

{

    "contextResponses": [

        {

            "contextElement": {

                "attributes": [

                    {

                        "name": "attrName",

                        "values": [

                            {

                                "recvTime": "2014-02-14T13:43:33.306Z",

                                "attrValue": "21.28"

                            },

                            {

                                "recvTime": "2014-02-14T13:43:34.636Z",

                                "attrValue": "23.42"

                            },

                            {

                                "recvTime": "2014-02-14T13:43:35.424Z",

                                "attrValue": "22.12"

                            }

                        ]

                    }

                ],

                "id": "entityId",

                "isPattern": false

            },

            "statusCode": {

                "code": "200",

                "reasonPhrase": "OK"

            }

        }

    ]

}

```



##img test con código img izquierda y código a la derecha

asdfadfasdf
asdfasd
<div></div>
```.json

{

    "contextResponses": [

        {

            "contextElement": {

                "attributes": [

                    {

                        "name": "attrName",

                        "values": [

                            {

                                "recvTime": "2014-02-14T13:43:33.306Z",

                                "attrValue": "21.28"

                            },

                            {

                                "recvTime": "2014-02-14T13:43:34.636Z",

                                "attrValue": "23.42"

                            },

                            {

                                "recvTime": "2014-02-14T13:43:35.424Z",

                                "attrValue": "22.12"

                            }

                        ]

                    }

                ],

                "id": "entityId",

                "isPattern": false

            },

            "statusCode": {

                "code": "200",

                "reasonPhrase": "OK"

            }

        }

    ]

}

```

![texto alternativo2](http://hivdb.stanford.edu/images/schema.gif)



##text link cruzado

[This link](../user/archivo.md)