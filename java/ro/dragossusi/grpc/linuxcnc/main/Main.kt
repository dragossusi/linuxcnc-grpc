package ro.dragossusi.grpc.linuxcnc.main

import io.grpc.ManagedChannelBuilder
import ro.dragossusi.proto.linuxcnc.*
import java.util.concurrent.TimeUnit
import java.util.logging.Logger

private val logger = Logger.getLogger("Main")

fun main() {
    val channel = ManagedChannelBuilder.forTarget("localhost:50051")
        .usePlaintext()
        .build()
    try {
        LinuxCncGrpc.newBlockingStub(channel).apply {
            addComp()
            getComp()
            readStatus()
        }
    } finally {
        channel.shutdownNow()
            .awaitTermination(5, TimeUnit.SECONDS)
    }
}

private fun LinuxCncGrpc.LinuxCncBlockingStub.readStatus() {
    val request = readStatusRequest {
        // no-op
    }
    val status = readStatus(request)

    logger.info("Status: \n$status")
}

private fun LinuxCncGrpc.LinuxCncBlockingStub.addComp() {
    val request = createComponentRequest {
        name = "test_comp"
    }
    val component = createComponent(request)
    logger.info("Created component: \n$component")
}

private fun LinuxCncGrpc.LinuxCncBlockingStub.getComp() {
    val request = getComponentsRequest {
        // no-op
    }
    val components = getComponents(request).componentsList
    logger.info("Received ${components.size} components: \n$components")
}